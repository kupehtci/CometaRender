//
// Created by Daniel Laplana Gimeno on 19/1/25.
//
#define GL_SILENCE_DEPRECATION

#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <core/Application.h>
#include <input/Input.h>

#include "render/Renderer.h"
#include "core/Application.h"


// ------------ FUNCTION DECLARATION ------------
/**
 * Callback to handle the window resize through OpenGL function
 * @param window Window pointer passed through the OpenGL callback
 * @param width New width passed through the OpenGL callback
 * @param height New height passed through the OpenGL callback
 */
void HandleResizeCallback(GLFWwindow *window, int width, int height);


// Window constructor
Window::Window()
{
    this->_resolution = nullptr;
    this->_window = nullptr;
    this->_title = "none";
}

/**
 * Window destructor
 */
Window::~Window(){
    if(this->_window !=  nullptr){
        glfwDestroyWindow(this->_window);
        delete _window;
    }

    delete _resolution;
}




void Window::Create(int width, int height, const char *title) {

    // Store resolution parameters
    _resolution = new Quad(width, height);
    this->_title = title;


    // Create a GLFW window
    this->_window = glfwCreateWindow(width,height, title, NULL, NULL);

    if (!_window) {
        glfwTerminate();
        return;
    }

    // Set Callbacks
    glfwSetWindowSizeCallback(_window, HandleResizeCallback);

    glfwMakeContextCurrent(_window);
}

void Window::Init() {

}


void Window::Update() {
    // Render();
}


void Window::SwapBuffers() {

//    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);         // Clear the screen

    glfwSwapBuffers(_window);
    glfwPollEvents();
    glEnable(GL_DEPTH_TEST); 
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);         // Clear the screen
}




bool Window::ShouldHandleCloseWindow(){
    return glfwWindowShouldClose(this->_window);
}

/**
 * Close the window and clean it
 * Also clean the rest of parameters of the window
 */
void Window::Close() {

    if(this->_window !=  nullptr){
        glfwDestroyWindow(this->_window);
    }

    delete this->_resolution;
    this->_resolution = nullptr;

    COMETA_ASSERT(("Window " + (std::string)this->_title +  " closed correctly").c_str());
}

/**
 * Handle the resize of the window
 */
void Window::HandleResize(GLFWwindow* window, int width, int height) {
    Quad previousResolution = *_resolution;

    // glfwGetWindowSize(_window, &_resolution->x, &_resolution->y);
    glfwGetFramebufferSize(_window, &_resolution->x, &_resolution->y);
    
    // COMETA_ASSERT(("Handling resize from " + std::to_string(previousResolution.x)  + ", " + std::to_string(previousResolution.y) + " to " + std::to_string(_resolution->x) + ", " + std::to_string(_resolution->y)).c_str());

    // modify viewport resolution
    glViewport( 0.f, 0.f, _resolution->x, _resolution->y);
}


/**
 * Callback that is called from GLFW library and calls the Window HandleResize method to handle the resize of the window
 * This function is called from OpenGL as a callback
 * @param window (GLFWwindow*) window pointer of the main window that is being resized
 * @param width (int) new width value of the window
 * @param height (int) new height value of the window
 */
void HandleResizeCallback(GLFWwindow* window, int width, int height){
    Window::GetInstancePtr()->HandleResize(window, width, height);
}


// Previus used function to show colors
void TestingFunctionShaderColors(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // ------------------------------------------------------------------------------------
    // TESTING
    // ------------------------------------------------------------------------------------

    Shader mainShader = Shader("Main Shader", "src/render/shaders/vertex_shader.vert", "src/render/shaders/fragment_shader.frag");

    // Set shader as current and delete the compiled shaders
    glUseProgram(mainShader.GetShaderUID());

    float vertices[] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // left
            0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // right
            0.0f,  0.5f, 0.0f ,  0.0f, 0.0f, 1.0f, // top
    };

    // Testing uniform value update
    float timeValue = glfwGetTime();
    float greenValue = sin(timeValue) / 2.0f + 0.5f;
    mainShader.SetFloat3("attrColor", glm::vec3(1.0f, greenValue, greenValue));

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attr
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attr
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // draw our first triangle
    glUseProgram(mainShader.GetShaderUID());
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_TRIANGLES, 0, 3);


    // Once all is used, delete the resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    mainShader.Delete();
}