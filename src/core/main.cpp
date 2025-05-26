//
//// #define GLFW_INCLUDE_VULKAN
//

#include <filesystem>
#include <iostream>

#include "render/Renderer.h"
#include "render/Transform.h"
#include "render/Material.h"
#include "render/Mesh.h"
#include "input/Input.h"
#include "render/Shader.h"

int main() {

    // Application* app = Application::GetInstancePtr();
    // app->Init();
    // app->Running();
    // app->Close();
    //
    // delete app;

    Renderer::Create();
    Renderer* _renderer = Renderer::GetInstancePtr();

    Input::Create();
    Input* _input = Input::GetInstancePtr();

    Time::Create();
    Time* _time = Time::GetInstancePtr();

    _renderer->Init();
    _input->Init();
    _time->Init();

    // Initialize main components
    Camera* currentCamera = new Camera();
    _renderer->SetCamera(currentCamera);

    // Create a transform for the cube
    Transform* cubeTransform = new Transform();
    cubeTransform->position = glm::vec3(0.0, 0.0, -5.0f);
    cubeTransform->rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    cubeTransform->scale = glm::vec3(1.0f, 1.0f, 1.0f);

    // Create material
    auto brickMaterial = std::make_shared<Material>(glm::vec3(1.0f, 1.0f, 1.0f),
                                    glm::vec3(1.0f, 0.5f, 0.31f),
                                    glm::vec3(1.0f, 0.5f, 0.31f),
                                    glm::vec3(0.5f, 0.5f, 0.5f),
                                    64.0f,
                                    "resources/bricks_diffuse_map.jpg",
                                    "resources/white.jpg",
                                    "resources/black.jpg");

    brickMaterial->LoadShader("Blinn phong shader",
        "src/render/shaders/light_map_shader.vert",
    "src/render/shaders/light_map_shader.frag" );

    // Geometry definition
    float vertices[] = {
        // positions          // normals           // colors            // texture coords
        // Front face
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,

        // Back face
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,

        // Top face
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,

        // Bottom face
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f, 0.0f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f, 0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f,

        // Right face
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,  0.0f, 0.0f,

        // Left face
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f, 1.0f,  0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f, 1.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f, 1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f, 1.0f,  0.0f, 1.0f
    };

    unsigned int indices[] = {
        0,  1,  2,    2,  3,  0,   // Front
        4,  5,  6,    6,  7,  4,   // Back
        8,  9,  10,   10, 11, 8,   // Top
        12, 13, 14,   14, 15, 12,  // Bottom
        16, 17, 18,   18, 19, 16,  // Right
        20, 21, 22,   22, 23, 20   // Left
    };

    // Create mesh
    std::shared_ptr<Mesh> brickMesh = std::make_shared<Mesh>();
    brickMesh->AddVertices(vertices, sizeof(vertices) / sizeof(float));
    brickMesh->AddIndices(indices, sizeof(indices) / sizeof(unsigned int));

    brickMesh->SetLayoutBuffer({
        {0, DataType::Float3, "aPos"},
        {1, DataType::Float3, "aNormal"},
        {2, DataType::Float3, "aColor"},
        {3, DataType::Float2, "aTexCoord"}
        });
    brickMesh->Build();

    // Create a renderable object using the new API
    std::shared_ptr<Renderable> cubeRenderable = _renderer->CreateRenderable(brickMesh, brickMaterial, cubeTransform);

    // Create light transform
    Transform* lightTransform = new Transform();
    lightTransform->position = glm::vec3(0.0f, 1.0f, -2.0f);
    lightTransform->scale = glm::vec3(0.2f, 0.2f, 0.2f);

    // Create point light using the new API
    std::shared_ptr<PointLight> pointLight = _renderer->CreatePointLight(lightTransform);
    pointLight->SetAmbient(glm::vec3(0.2f, 0.2f, 0.2f));
    pointLight->SetDiffuse(glm::vec3(0.8f, 0.8f, 0.8f));
    pointLight->SetSpecular(glm::vec3(1.0f, 1.0f, 1.0f));

    // Create a light mesh (optional, for visualization)
    auto lightMaterial = std::make_shared<Material>(glm::vec3(1.0f, 1.0f, 1.0f),
                                    glm::vec3(1.0f, 1.0f, 1.0f),
                                    glm::vec3(1.0f, 1.0f, 1.0f),
                                    glm::vec3(1.0f, 1.0f, 1.0f),
                                    2.0f,
                                    "resources/white.jpg",
                                    "resources/white.jpg",
                                    "resources/black.jpg");
    lightMaterial->LoadShader("Light Shader","src/render/shaders/light_shader.vert", "src/render/shaders/light_shader.frag");
    auto lightMesh = Mesh::CreateSphere();
    

    std::shared_ptr<Renderable> lightRenderable = _renderer->CreateRenderable(lightMesh, lightMaterial, lightTransform);

    bool _applicationRunning = true;
    while (_applicationRunning)
    {
        _renderer->Update();
        _input->Update();
        _time->Update();

        if (Input::IsKeyPressed(GLFW_KEY_ESCAPE) ||
            Renderer::ShouldClose()){ _applicationRunning = false;}

        _renderer->Render(); 
    }

    delete cubeTransform;
    delete lightTransform;
    delete currentCamera;

    _time->Close();
    _input->Close();
    _renderer->Close();

    return 0;
}

