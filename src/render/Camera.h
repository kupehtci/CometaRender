//
// Created by Daniel Laplana Gimeno on 12/2/25.
//

#ifndef AURAGL_CAMERA_H
#define AURAGL_CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

#include "../debug/Assertion.h"
#include "../core/Time.h"

class Camera {
private:
    
    glm::vec3 _position; 
    glm::vec3 _direction; 
    glm::vec3 _up;
    glm::vec3 _right;

    float _fov;
    float _pitch;  
    float _yaw;

    float _near; 
    float _far;

    float _movementSpeed; 
    float _sensitivity; 

    glm::mat4 _projectionMatrix;
    glm::mat4 _viewMatrix;


public:
    Camera();
    
    Camera(glm::mat4 projectionMatrix, glm::mat4 viewMatrix);

    ~Camera();


    // Methods

    /**
    * Not implemented yet
    */
    void OnUpdate(); 


    // --------- GETTERS ---------
public: 
    glm::vec3 GetPosition() { return _position;  }
    glm::mat4 GetProyectionMatrix() { return _projectionMatrix; }
    glm::mat4 GetViewMatrix() { return _viewMatrix;  }
    glm::mat4 GetViewProyection() { return _projectionMatrix * _viewMatrix; }
};


#endif //AURAGL_CAMERA_H
