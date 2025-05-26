//
// Created by Daniel Laplana Gimeno on 5/12/24.
//

#include "Renderer.h"
#include "../debug/Assertion.h"
#include "../../vendor/glad/include/glad/glad.h"

#define GLAD_GL_IMPLEMENTATION
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "render/FrameBuffer.h"
#include "render/Shader.h"
#include "render/Mesh.h"
#include "render/Material.h"
#include "render/Camera.h"

#include "render/Transform.h"


// IMGUI
// #include "imgui.h"
//// #include "backends/imgui_impl_glfw.h"
//// #include "backends/imgui_impl_opengl3.h"

Renderer::Renderer() {
    this->_window = nullptr;

    _depthCulling = true; 
    _faceCullingMode = FACE_CULLING_MODE::FACE_CULLING_NONE; 
}

Renderer::~Renderer() {
    if (_shadowFrameBuffer) {
        delete _shadowFrameBuffer;
        _shadowFrameBuffer = nullptr;
    }
    
    if (_pointShadowFrameBuffer) {
        delete _pointShadowFrameBuffer;
        _pointShadowFrameBuffer = nullptr;
    }
}

void Renderer::Init(){

    if(!glfwInit()){
        Assertion::Error("Cannot initialize GLFW, review GLFW installation");
        return;
    }
    
    // Intialize Hints depending on the platform
#ifdef PLATFORM_MACOS
    COMETA_ASSERT("Initializing OpenGL Forward compatibility for MacOS");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#elif PLATFORM_WINDOWS
    COMETA_ASSERT("Initializating OpenGL for Windows");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
#elif PLATFORM_LINUX
    COMETA_ASSERT("Initializating OpenGL for Linux");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
#endif

    // Indicate GLFW and OpenGL version
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a Window (Abstraction)
    _window = Window::GetInstancePtr();
    _window->Create(COMETA_DEFAULT_WIDTH, COMETA_DEFAULT_HEIGHT, "Cometa Render");

    std::cout << "glfwGetProcAddress address: " << (void*)glfwGetProcAddress << std::endl;

    // GLAD loading is made after initializating a window
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if (status == 0)
    {
        std::cout << "Failed to initialize GLAD, status code: " << status << std::endl;
        _window->Close();
        glfwTerminate();
        return;
    }

    //Set the initial viewport for NDC transformations
    //glViewport( 0.f, 0.f, COMETA_DEFAULT_WIDTH, COMETA_DEFAULT_HEIGHT);

    int frameBufferWidth, frameBufferHeight = 0; 
    glfwGetFramebufferSize(_window->GetGlfwWindow(), &frameBufferWidth, &frameBufferHeight);

    glViewport(0, 0, frameBufferWidth, frameBufferHeight);

    std::cout << "Renderer initialized: \n OpenGL version: " <<  glGetString(GL_VERSION);

    // Validate maximum number of vertex attributes to use in the shaders
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    COMETA_MSG("Maximum number of vertex attributes supported by hardware: " , std::to_string(nrAttributes));

    COMETA_MSG("Maximum number of textures in buffer: ", GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);

    if (_depthCulling) {
        glEnable(GL_DEPTH_TEST); 
    }

    // --------------- SHADOW INIT ---------------

    _shadowMapShader = Shader::LoadShader("Shadow Map shader", "src/render/shaders/shadow_map.vert", "src/render/shaders/shadow_map.frag");
    _pointShadowMapShader = Shader::LoadShader("Point Shadow Map shader", "src/render/shaders/point_shadow_map.vert", "src/render/shaders/point_shadow_map.frag", "src/render/shaders/point_shadow_map.geom");

}

void Renderer::Update(){
    // Update current window
    _window->Update();

    // Check if camera is set
    if (!_camera) {
        COMETA_MSG("[RENDERER][UPDATE] Camera is not set, cannot render");
        return;
    }
    
    // Update camera
    _camera->OnUpdate();

    // -------- DIRECTIONAL LIGHT SHADOW MAPPING PASS --------
    if (_directionalLight)
    {
        if (!_shadowFrameBuffer)
        {
            _shadowFrameBuffer = new FrameBuffer(SHADOW_MAP_WIDTH, SHADOW_MAP_HEIGHT);
        }
        _shadowFrameBuffer->Bind();

        glClear(GL_DEPTH_BUFFER_BIT);
        glCullFace(GL_FRONT);
        
        // Get the light space matrix from the directional light
        glm::mat4 lightSpaceMatrix = _directionalLight->GetLightSpaceMatrix();
        
        _shadowMapShader->Bind();
        
        for (auto& renderable : _renderables)
        {
            Transform* transform = renderable->GetTransform();
            
            // Set the model matrix and light space matrix
            _shadowMapShader->SetMatrix4("model", transform->GetWorldTransform());
            _shadowMapShader->SetMatrix4("lightSpaceMatrix", lightSpaceMatrix);
            
            // Draw the mesh
            renderable->GetMesh()->Bind();
            renderable->GetMesh()->Draw();
        }
        
        // Unbind the shadow framebuffer
        _shadowFrameBuffer->Unbind();
        
        // Reset face culling to default
        glCullFace(GL_BACK);
    }

    // -------- POINT LIGHT SHADOW MAPPING PASS --------
    // Render shadows for each point light
    if (!_pointLights.empty())
    {
        if (!_pointShadowFrameBuffer)
        {
            _pointShadowFrameBuffer = new CubeMapFrameBuffer(SHADOW_MAP_WIDTH, SHADOW_MAP_HEIGHT);
        }

        glCullFace(GL_FRONT); // Cull front faces during shadow pass

        _pointShadowMapShader->Bind();
        _pointShadowMapShader->SetFloat("far_plane", POINT_LIGHT_FAR_PLANE);

        // For now, only process the first point light
        if (!_pointLights.empty())
        {
            auto pointLight = _pointLights[0];
            Transform* lightTransform = pointLight->GetTransform();
            
            // Bind the framebuffer
            _pointShadowFrameBuffer->Bind();
            
            // Clear the depth buffer
            glClear(GL_DEPTH_BUFFER_BIT);
            
            // Set light position uniform
            _pointShadowMapShader->SetFloat3("lightPos", lightTransform->position);
            
            // Create shadow transformation matrices for each face of the cubemap
            glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, POINT_LIGHT_FAR_PLANE);
            std::vector<glm::mat4> shadowTransforms;
            
            // Right face (+X)
            shadowTransforms.push_back(shadowProj * 
                glm::lookAt(lightTransform->position, 
                            lightTransform->position + glm::vec3(1.0f, 0.0f, 0.0f), 
                            glm::vec3(0.0f, -1.0f, 0.0f)));
            // Left face (-X)
            shadowTransforms.push_back(shadowProj * 
                glm::lookAt(lightTransform->position, 
                            lightTransform->position + glm::vec3(-1.0f, 0.0f, 0.0f), 
                            glm::vec3(0.0f, -1.0f, 0.0f)));
            // Top face (+Y)
            shadowTransforms.push_back(shadowProj * 
                glm::lookAt(lightTransform->position, 
                            lightTransform->position + glm::vec3(0.0f, 1.0f, 0.0f), 
                            glm::vec3(0.0f, 0.0f, 1.0f)));
            // Bottom face (-Y)
            shadowTransforms.push_back(shadowProj * 
                glm::lookAt(lightTransform->position, 
                            lightTransform->position + glm::vec3(0.0f, -1.0f, 0.0f), 
                            glm::vec3(0.0f, 0.0f, -1.0f)));
            // Front face (+Z)
            shadowTransforms.push_back(shadowProj * 
                glm::lookAt(lightTransform->position, 
                            lightTransform->position + glm::vec3(0.0f, 0.0f, 1.0f), 
                            glm::vec3(0.0f, -1.0f, 0.0f)));
            // Back face (-Z)
            shadowTransforms.push_back(shadowProj * 
                glm::lookAt(lightTransform->position, 
                            lightTransform->position + glm::vec3(0.0f, 0.0f, -1.0f), 
                            glm::vec3(0.0f, -1.0f, 0.0f)));
            
            // Set the shadow matrices in the shader
            for (unsigned int j = 0; j < 6; ++j)
            {
                _pointShadowMapShader->SetMatrix4("shadowMatrices[" + std::to_string(j) + "]", shadowTransforms[j]);
            }
            
            // Render scene from light's perspective
            for (auto& renderable : _renderables)
            {
                Transform* transform = renderable->GetTransform();
                
                // Set the model matrix
                _pointShadowMapShader->SetMatrix4("model", transform->GetWorldTransform());
                
                // Draw the mesh
                renderable->GetMesh()->Bind();
                renderable->GetMesh()->Draw();
            }
        }
        
        // Unbind the framebuffer
        _pointShadowFrameBuffer->Unbind();
        
        // Reset face culling to default
        glCullFace(GL_BACK);
    }

    // -------- MAIN RENDERING PASS --------
    // Reset viewport to window size
    int frameBufferWidth, frameBufferHeight = 0; 
    glfwGetFramebufferSize(_window->GetGlfwWindow(), &frameBufferWidth, &frameBufferHeight);
    glViewport(0, 0, frameBufferWidth, frameBufferHeight);
    
    // Clear the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render each object with lighting
    for (auto& renderable : _renderables)
    {
        std::cout << "Rendering object" << std::endl;
        Transform* transform = renderable->GetTransform();

        renderable->GetMaterial()->Bind();
        renderable->GetMesh()->Bind();

        std::shared_ptr<Shader> shader = renderable->GetMaterial()->GetShader();
        shader->Bind();

        // Set the number of point lights
        shader->SetInt("number_lights", static_cast<int>(_pointLights.size()));

        // Bind the directional light
        if (_directionalLight)
        {
            shader->SetFloat3("directionalLight.direction", _directionalLight->GetDirection());
            shader->SetFloat3("directionalLight.ambient", _directionalLight->GetAmbient());
            shader->SetFloat3("directionalLight.diffuse", _directionalLight->GetDiffuse());
            shader->SetFloat3("directionalLight.specular", _directionalLight->GetSpecular());
            
            // Set the light space matrix for shadow mapping
            shader->SetMatrix4("lightSpaceMatrix", _directionalLight->GetLightSpaceMatrix());
            
            // Bind the shadow map texture
            if (_shadowFrameBuffer)
            {
                // Bind the shadow map to texture unit 5 (arbitrary choice)
                _shadowFrameBuffer->BindDepthTexture(GL_TEXTURE5);
                shader->SetInt("shadowMap", 5);
            }
            
            // Bind the point shadow map texture if it exists
            if (_pointShadowFrameBuffer)
            {
                // Bind the point shadow map to texture unit 6 (arbitrary choice)
                _pointShadowFrameBuffer->BindDepthCubeMap(GL_TEXTURE6);
                shader->SetInt("pointShadowMap", 6);
                shader->SetFloat("far_plane", POINT_LIGHT_FAR_PLANE);
            }
        }

        // Bind each point light to the shader
        for (size_t i = 0; i < _pointLights.size(); ++i)
        {
            auto pointLight = _pointLights[i];
            Transform* lightTransform = pointLight->GetTransform();
            
            std::string light_string = "lights[" + std::to_string(i) + "]";
            shader->SetFloat3(light_string + ".position", lightTransform->position);
            shader->SetFloat3(light_string + ".ambient", pointLight->GetAmbient());
            shader->SetFloat3(light_string + ".diffuse", pointLight->GetDiffuse());
            shader->SetFloat3(light_string + ".specular", pointLight->GetSpecular());
            shader->SetFloat(light_string + ".constant", pointLight->GetConstant());
            shader->SetFloat(light_string + ".linear", pointLight->GetLinear());
            shader->SetFloat(light_string + ".quadratic", pointLight->GetQuadratic());
        }

        shader->SetMatrix4("uViewProjection", _camera->GetViewProyection());
        shader->SetFloat3("uViewPos", _camera->GetPosition());
        shader->SetMatrix4("uModel", transform->GetWorldTransform());

        shader->Bind();
        renderable->GetMesh()->Draw();
    }
}

// Factory methods for creating rendering objects
std::shared_ptr<Renderable> Renderer::CreateRenderable(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material, Transform* transform) {
    auto renderable = std::make_shared<Renderable>(mesh, material, transform);
    _renderables.push_back(renderable);
    return renderable;
}

std::shared_ptr<PointLight> Renderer::CreatePointLight(Transform* transform) {
    auto pointLight = std::make_shared<PointLight>(transform);
    _pointLights.push_back(pointLight);
    return pointLight;
}

std::shared_ptr<DirectionalLight> Renderer::CreateDirectionalLight(Transform* transform) {
    // Only one directional light is supported
    if (_directionalLight) {
        COMETA_WARNING("[RENDERER] Only one directional light is supported. Replacing existing directional light.");
    }
    
    _directionalLight = std::make_shared<DirectionalLight>(transform);
    return _directionalLight;
}

void Renderer::Render()
{
    // Swap buffers to render into screen
    _window->SwapBuffers();
}

void Renderer::Close(){

    _window->Close();
    glfwTerminate();
}


