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

#include "world/WorldManager.h"
#include "world/ComponentStorage.h"
#include "world/Components.h"
#include "world/Entity.h"


Renderer::Renderer() {
    this->_window = nullptr;

    _depthCulling = true; 
    _faceCullingMode = FACE_CULLING_MODE::FACE_CULLING_NONE; 
}

Renderer::~Renderer() {
    
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
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE); // TODO: Remove this, only for testing
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
    _window->Create(COMETA_DEFAULT_WIDTH, COMETA_DEFAULT_HEIGHT, "CometA");

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
    COMETA_MSG(("Maximum number of vertex attributes supported by hardware: ", std::to_string(nrAttributes)).c_str());

    COMETA_MSG("Maximum number of textures in buffer: ", GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);

    if (_depthCulling) {
        glEnable(GL_DEPTH_TEST); 
    }


}

void Renderer::Update(){
    // Update current window
    _window->Update();

    // render the world elements
    WorldManager* worldManager = WorldManagerRef;
    std::shared_ptr<World> currentWorld = worldManager->GetCurrentWorld();

    if (currentWorld == nullptr)
    {
        COMETA_MSG("[RENDERER] Current world is not set, cannot render");
        return;
    }

    // iterate only through renderable components
    ComponentStorage<MeshRenderable>& _renderables = currentWorld->GetComponentRegistry().GetStorage<MeshRenderable>();

    // std::cout << "================= PROCESSING RENDERABLES IN RENDERER =================" << std::endl;
    // for (auto renderable : _renderables)
    // {
    //     std::cout << "Processing renderable from entity: " << renderable.GetOwner()->GetUID() << std::endl;
    // }
    // std::cout << "================= END UP PROCESSING RENDERABLES =================" << std::endl;



    // Swap buffers to render into screen
    _window->SwapBuffers();
}

void Renderer::Close(){
    _window->Close();
    glfwTerminate();
}


