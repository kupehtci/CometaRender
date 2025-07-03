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
    [[nodiscard]] glm::vec3 GetPosition() { return _position;  }
    [[nodiscard]] glm::vec3 GetDirection() { return _direction;  }
    [[nodiscard]] glm::vec3 GetUp() { return _up;  }
    [[nodiscard]] glm::vec3 GetRight() { return _right;  }

    [[nodiscard]] float GetNear() { return _near; }
    [[nodiscard]] float GetFar() { return _far; }
    [[nodiscard]] float GetFov() { return _fov; }

    [[nodiscard]] glm::mat4 GetProyectionMatrix() { return _projectionMatrix; }
    [[nodiscard]] glm::mat4 GetViewMatrix() { return _viewMatrix;  }
    [[nodiscard]] glm::mat4 GetViewProyection() { return _projectionMatrix * _viewMatrix; }

    // --------- SETTERS ---------
public:
    void SetPosition(glm::vec3 position) { _position = position; }
    void SetDirection(glm::vec3 direction) { _direction = direction; }
    void SetUp(glm::vec3 up) { _up = up; }
    void SetRight(glm::vec3 right) { _right = right; }

    void SetNear(float near) { _near = near; }
    void SetFar(float far) { _far = far; }
    void SetFov(float fov) { _fov = fov; }

    /**
    * not recomendable to use
    */
    void SetProyectionMatrix(glm::mat4 projectionMatrix) { _projectionMatrix = projectionMatrix; }

    /**
    * not recomendable to use
    */
    void SetViewMatrix(glm::mat4 viewMatrix) { _viewMatrix = viewMatrix; }

};


#endif //AURAGL_CAMERA_H
