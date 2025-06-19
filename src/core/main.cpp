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

    // Create material for cubes
    auto brickMaterial = std::make_shared<Material>(
        glm::vec3(1.0f, 1.0f, 1.0f), // color
        glm::vec3(1.0f, 0.5f, 0.31f), // ambient
        glm::vec3(1.0f, 0.5f, 0.31f), // diffuse
        glm::vec3(0.5f, 0.5f, 0.5f),  // specular
        64.0f,
        "resources/bricks_diffuse_map.jpg",
        "resources/bricks_specular_map.jpg",
        "resources/black.jpg"
    );

    brickMaterial->LoadShader("Blinn phong shader",
        "src/render/shaders/blinn_phong_shader.vert",
        "src/render/shaders/blinn_phong_shader.frag" );

    // Wave animation setup
    std::vector<Transform*> cubeTransforms;
    const int gridSize = 12;
    const float spacing = 1.2f;

    for (int x = 0; x < gridSize; ++x) {
        for (int z = 0; z < gridSize; ++z) {
            float xpos = (x - gridSize / 2) * spacing;
            float zpos = (z - gridSize / 2) * spacing;
            float ypos = 0.5f; // base height
            Transform* cubeTransform = new Transform();
            cubeTransform->position = glm::vec3(xpos, ypos, zpos - 5.0f);
            cubeTransform->rotation = glm::vec3(0.0f, 0.0f, 0.0f);
            cubeTransform->scale = glm::vec3(1.0f, 1.0f, 1.0f);
            _renderer->CreateRenderable(Mesh::CreateBox(0.5f), brickMaterial, cubeTransform);
            cubeTransforms.push_back(cubeTransform);
        }
    }

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

    // Second floor
    auto floorTransform2 = new Transform();
    floorTransform2->position = glm::vec3(-1.0f, 7.1f, -16.0f);
    floorTransform2->scale = glm::vec3(-20.0f, -1.0f, -20.0f);
    floorTransform2->rotation = glm::vec3(-124.0f, 0.0f, 0.0f);

    auto floorRenderable2 = _renderer->CreateRenderable(Mesh::CreatePlane(), floorMaterial, floorTransform2);

    // Directional Light
    auto directionalLightTransform = new Transform();
    auto directionalLight = _renderer->CreateDirectionalLight(directionalLightTransform);


    // Main rendering loop
    bool _applicationRunning = true;
    while (_applicationRunning)
    {
        float t = _time->GetDeltaTime();
        // Animate cubes in a wave
        int idx = 0;
        for (int x = 0; x < gridSize; ++x) {
            for (int z = 0; z < gridSize; ++z) {
                float phase = (float)x * 0.5f + (float)z * 0.5f;
                float amplitude = 3.5f;
                cubeTransforms[idx]->position.y = 0.5f + amplitude * sinf(_time->GetAccumulatedTime() + phase);
                idx++;
            }
        }
        _renderer->Update();
        _input->Update();
        _time->Update();
        _uimanager->Update();
        if (Input::IsKeyPressed(GLFW_KEY_ESCAPE) || Renderer::ShouldClose()) { _applicationRunning = false; }
        _renderer->Render(); 
    }

    delete lightTransform;
    delete currentCamera;

    _uimanager->Close();
    _time->Close();
    _input->Close();
    _renderer->Close();

    return 0;
}

