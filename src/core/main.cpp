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

    brickMaterial->LoadShader("Movement Blinn Phong Shader",
        "src/render/shaders/blinn_phong_shader.vert",
        "src/render/shaders/blinn_phong_shader.frag" );

    // Wave animation setup
    std::vector<Transform*> cubeTransforms;
    const int gridSize = 15;
    const float spacing = 0.5f;

    for (int x = 0; x < gridSize; ++x) {
        for (int z = 0; z < gridSize; ++z) {
            float xpos = (x - gridSize / 2) * spacing;
            float zpos = (z - gridSize / 2) * spacing;
            float ypos = 0.5f; // base height
            Transform* cubeTransform = new Transform();
            cubeTransform->position = glm::vec3(xpos, ypos, zpos - 5.0f);
            cubeTransform->rotation = glm::vec3(0.0f, 0.0f, 0.0f);
            cubeTransform->scale = glm::vec3(0.2f, 0.2f, 0.2f);
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
    floorTransform->position = glm::vec3(0.0f, -1.0f, -5.0f);
    floorTransform->scale = glm::vec3(20.0f, 20.0f, 20.0f); // Increased size

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

    // Create a room with walls
    float wallSize = 20.0f;
    float halfWall = wallSize * 0.5f;
    float roomHeight = 18.0f;
    // Back 
    Transform* backWall = new Transform();
    backWall->position = glm::vec3(0.0f, halfWall - 1.0f, -5.0f - halfWall);
    backWall->scale = glm::vec3(wallSize, wallSize, wallSize);
    backWall->rotation = glm::vec3(-90.0f, 180.0f, 0.0f);
    _renderer->CreateRenderable(Mesh::CreatePlane(), floorMaterial, backWall);
    // Left 
    Transform* leftWall = new Transform();
    leftWall->position = glm::vec3(-halfWall, halfWall - 1.0f, -5.0f);
    leftWall->scale = glm::vec3(wallSize, wallSize, wallSize);
    leftWall->rotation = glm::vec3(0.0f, -90.0f, 90.0f);
    _renderer->CreateRenderable(Mesh::CreatePlane(), floorMaterial, leftWall);
    // Right
    Transform* rightWall = new Transform();
    rightWall->position = glm::vec3(halfWall, halfWall - 1.0f, -5.0f);
    rightWall->scale = glm::vec3(wallSize, wallSize, wallSize);
    rightWall->rotation = glm::vec3(0.0f, -90.0f, -90.0f);
    _renderer->CreateRenderable(Mesh::CreatePlane(), floorMaterial, rightWall);
    // Front
    Transform* frontWall = new Transform();
    frontWall->position = glm::vec3(0.0f, halfWall - 1.0f, -5.0f + halfWall);
    frontWall->scale = glm::vec3(wallSize, wallSize, wallSize);
    frontWall->rotation = glm::vec3(-90.0f, 0.0f, 180.0f);
    _renderer->CreateRenderable(Mesh::CreatePlane(), floorMaterial, frontWall);
    // Top
    Transform* ceiling = new Transform();
    ceiling->position = glm::vec3(0.0f, roomHeight - 1.0f, -5.0f);
    ceiling->scale = glm::vec3(wallSize, wallSize, wallSize);
    ceiling->rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    _renderer->CreateRenderable(Mesh::CreatePlane(), floorMaterial, ceiling);

    // Directional Light
    auto directionalLightTransform = new Transform();
    auto directionalLight = _renderer->CreateDirectionalLight(directionalLightTransform);


    // Main rendering loop
    bool _applicationRunning = true;
    while (_applicationRunning)
    {
        float t = _time->GetAccumulatedTime();
        // Set uTime uniform for GPU-side animation
        brickMaterial->GetShader()->Bind();
        brickMaterial->GetShader()->SetFloat("uTime", t);
        // // Animate cubes in a wave

        int idx = 0;
        for (int x = 0; x < gridSize; ++x) {
            for (int z = 0; z < gridSize; ++z) {
                float phase = (float)x * 0.5f + (float)z * 0.5f;
                float amplitude = 0.5f;
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

