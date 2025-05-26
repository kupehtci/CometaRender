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
    Renderer::Create();
    Renderer* _renderer = Renderer::GetInstancePtr();

    Input::Create();
    Input* _input = Input::GetInstancePtr();

    Time::Create();
    Time* _time = Time::GetInstancePtr();

    UIManager::Create();
    UIManager* _uimanager = UIManager::GetInstancePtr();

    _renderer->Init();
    _input->Init();
    _time->Init();
    _uimanager->Init();

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
                                    "resources/bricks_specular_map.jpg",
                                    "resources/black.jpg");

    brickMaterial->LoadShader("Blinn phong shader",
        "src/render/shaders/blinn_phong_shader.vert",
    "src/render/shaders/blinn_phong_shader.frag" );

    // Create a renderable object
    std::shared_ptr<Renderable> cubeRenderable = _renderer->CreateRenderable(Mesh::CreateBox(0.5f), brickMaterial, cubeTransform);


    // Create point light
    Transform* lightTransform = new Transform();
    lightTransform->position = glm::vec3(0.0f, 1.0f, -2.0f);
    lightTransform->scale = glm::vec3(0.2f, 0.2f, 0.2f);
    std::shared_ptr<PointLight> pointLight = _renderer->CreatePointLight(lightTransform);
    pointLight->SetAmbient(glm::vec3(0.2f, 0.2f, 0.2f));
    pointLight->SetDiffuse(glm::vec3(0.8f, 0.8f, 0.8f));
    pointLight->SetSpecular(glm::vec3(1.0f, 1.0f, 1.0f));

    // Create a light mesh
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

    // Create a renderable that doesnt cast shadow
    std::shared_ptr<Renderable> lightRenderable = _renderer->CreateRenderable(lightMesh, lightMaterial, lightTransform);
    lightRenderable->SetCastShadow(false);

    // Floor renderable
    Transform* floorTransform = new Transform();
    floorTransform->position = glm::vec3(-1.0f, -1.0f, -1.0f);
    floorTransform->scale = glm::vec3(20.0f, 20.0f, 20.0f);

    auto floorMaterial = std::make_shared<Material>(glm::vec3(0.66f, 0.75f, 0.66f),
                                    glm::vec3(1.0f, 0.5f, 0.31f),
                                    glm::vec3(1.0f, 0.5f, 0.31f),
                                    glm::vec3(0.5f, 0.5f, 0.5f),
                                    64.0f,
                                    "resources/white.jpg",
                                    "resources/white.jpg",
                                    "resources/black.jpg");

    floorMaterial->LoadShader("Blinn phong shader",
        "src/render/shaders/blinn_phong_shader.vert",
    "src/render/shaders/blinn_phong_shader.frag" );


    auto floorRenderable = _renderer->CreateRenderable(Mesh::CreatePlane(), floorMaterial, floorTransform);

    // Second floot

    // Directional Light
    auto directionalLightTransform = new Transform();
    auto directionalLight = _renderer->CreateDirectionalLight(directionalLightTransform);

    // Main rendering loop
    bool _applicationRunning = true;
    while (_applicationRunning)
    {
        _renderer->Update();
        _input->Update();
        _time->Update();
        _uimanager->Update();

        if (Input::IsKeyPressed(GLFW_KEY_ESCAPE) ||
            Renderer::ShouldClose()){ _applicationRunning = false;}

        _renderer->Render(); 
    }

    delete cubeTransform;
    delete lightTransform;
    delete currentCamera;

    _uimanager->Close();
    _time->Close();
    _input->Close();
    _renderer->Close();

    return 0;
}

