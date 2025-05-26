// Created by Daniel Laplana Gimeno on 5/12/24.


// #define GL_SILENCE_DEPRECATION

#define GLAD_GL_IMPLEMENTATION
#define GLFW_INCLUDE_NONE


#ifndef AURAGL_RENDERER_H
#define AURAGL_RENDERER_H

#include "render/FrameBuffer.h"
#include "render/CubeMapFrameBuffer.h"
#include "core/CometaDefaults.h"
#include "core/Singleton.h"
#include "render/Window.h"
#include "render/Renderable.h"
#include "UI/UIManager.h"
#include <memory>
#include <vector>
#include <glm.hpp>

// Forward declarations
class Mesh;
class Material;
class Camera;
class Transform;


enum FACE_CULLING_MODE {
    FACE_CULLING_NONE = 0, 
    FACE_CULLING_CLOCKWISE = 1, 
    FACE_CULLING_COUNTER_CLOCKWISE = 2
};


// Base class for all lights
class Light {
protected:
    glm::vec3 _ambient = glm::vec3(0.2f, 0.2f, 0.2f);
    glm::vec3 _diffuse = glm::vec3(0.7f, 0.7f, 0.7f);
    glm::vec3 _specular = glm::vec3(1.0f, 1.0f, 1.0f);
    Transform* _transform;

public:
    Light(Transform* transform) : _transform(transform) {}
    virtual ~Light() = default;
    
    // Getters
    glm::vec3 GetAmbient() const { return _ambient; }
    glm::vec3 GetDiffuse() const { return _diffuse; }
    glm::vec3 GetSpecular() const { return _specular; }
    Transform* GetTransform() const { return _transform; }
    
    // Setters
    void SetAmbient(const glm::vec3& ambient) { _ambient = ambient; }
    void SetDiffuse(const glm::vec3& diffuse) { _diffuse = diffuse; }
    void SetSpecular(const glm::vec3& specular) { _specular = specular; }
    void SetTransform(Transform* transform) { _transform = transform; }
};

// Point light implementation
class PointLight : public Light {
private:
    float _constant = 1.0f;
    float _linear = 0.07f;
    float _quadratic = 0.017f;

public:
    PointLight(Transform* transform) : Light(transform) {}
    
    // Getters
    float GetConstant() const { return _constant; }
    float GetLinear() const { return _linear; }
    float GetQuadratic() const { return _quadratic; }
    
    // Setters
    void SetConstant(float constant) { _constant = constant; }
    void SetLinear(float linear) { _linear = linear; }
    void SetQuadratic(float quadratic) { _quadratic = quadratic; }
};

// Directional light implementation
class DirectionalLight : public Light {
private:
    glm::vec3 _direction = glm::vec3(-0.2f, -1.0f, -0.3f);
    
    // Shadow mapping properties
    float _shadowNearPlane = 1.0f;
    float _shadowFarPlane = 25.0f;
    float _shadowOrthoSize = 10.0f;
    
    // Cached light space matrix
    glm::mat4 _lightSpaceMatrix = glm::mat4(1.0f);
    bool _lightSpaceMatrixDirty = true;

    // Recalculate the light space matrix
    void UpdateLightSpaceMatrix() {
        // Create light projection matrix (orthographic for directional light)
        glm::mat4 lightProjection = glm::ortho(
            -_shadowOrthoSize, _shadowOrthoSize,
            -_shadowOrthoSize, _shadowOrthoSize,
            _shadowNearPlane, _shadowFarPlane);

        // Create light view matrix
        glm::vec3 lightPos = -_direction * 10.0f; // Position light far away in the opposite direction
        glm::mat4 lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        // Calculate light space matrix
        _lightSpaceMatrix = lightProjection * lightView;
        _lightSpaceMatrixDirty = false;
    }

public:
    DirectionalLight(Transform* transform) : Light(transform) {}
    
    // Getters
    glm::vec3 GetDirection() const { return _direction; }
    float GetShadowNearPlane() const { return _shadowNearPlane; }
    float GetShadowFarPlane() const { return _shadowFarPlane; }
    float GetShadowOrthoSize() const { return _shadowOrthoSize; }
    
    glm::mat4 GetLightSpaceMatrix() {
        if (_lightSpaceMatrixDirty) {
            UpdateLightSpaceMatrix();
        }
        return _lightSpaceMatrix;
    }
    
    // Setters
    void SetDirection(const glm::vec3& direction) { 
        _direction = direction; 
        _lightSpaceMatrixDirty = true;
    }
    
    void SetShadowNearPlane(float nearPlane) { 
        _shadowNearPlane = nearPlane; 
        _lightSpaceMatrixDirty = true;
    }
    
    void SetShadowFarPlane(float farPlane) { 
        _shadowFarPlane = farPlane; 
        _lightSpaceMatrixDirty = true;
    }
    
    void SetShadowOrthoSize(float size) { 
        _shadowOrthoSize = size; 
        _lightSpaceMatrixDirty = true;
    }
};

class Renderer : public SingletonManager<Renderer>{
    friend class Application;

private:
    Window* _window;

    bool _depthCulling = true;
    FACE_CULLING_MODE _faceCullingMode = FACE_CULLING_MODE::FACE_CULLING_CLOCKWISE; 
    
    // Shadow mapping properties
    static const unsigned int SHADOW_MAP_WIDTH = 1024;
    static const unsigned int SHADOW_MAP_HEIGHT = 1024;
    constexpr static const float POINT_LIGHT_FAR_PLANE = 25.0f;
    
    // Directional light shadow mapping
    FrameBuffer* _shadowFrameBuffer = nullptr;
    std::shared_ptr<Shader> _shadowMapShader = nullptr;

    // Point light shadow mapping
    CubeMapFrameBuffer* _pointShadowFrameBuffer = nullptr;
    std::shared_ptr<Shader> _pointShadowMapShader = nullptr;
    
    // Rendering objects
    std::vector<std::shared_ptr<Renderable>> _renderables;
    std::vector<std::shared_ptr<PointLight>> _pointLights;
    std::shared_ptr<DirectionalLight> _directionalLight;
    Camera* _camera = nullptr;

public:
    Renderer();
    ~Renderer() override;

public:
    void Init() override;
    void Update() override;
    void Close() override;

    void Render();

    // Create renderable objects
    std::shared_ptr<Renderable> CreateRenderable(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material, Transform* transform);
    std::vector<std::shared_ptr<Renderable>>& GetRenderables() { return _renderables; }
    
    // Light management
    std::shared_ptr<PointLight> CreatePointLight(Transform* transform);
    std::vector<std::shared_ptr<PointLight>>& GetPointLights() {return _pointLights; }
    std::shared_ptr<DirectionalLight> CreateDirectionalLight(Transform* transform);
    std::shared_ptr<DirectionalLight>& GetDirectionalLight() {return _directionalLight; }

    
    // Camera Management
    void SetCamera(Camera* camera) { _camera = camera; }
    Camera* GetCamera() const { return _camera; }

    [[nodiscard]] inline Window* GetWindow() const { return _window; }
    inline static bool ShouldClose () { return glfwWindowShouldClose(Renderer::GetInstancePtr()->GetWindow()->GetGlfwWindow()); }

    inline void SetDepthCulling(bool value) { _depthCulling = value; }
    inline void SetFaceCulling(FACE_CULLING_MODE value) {
    }
};

#define CometaRenderer Renderer::GetInstancePtr()

#endif //AURAGL_RENDERER_H
