//
// Created by Daniel Laplana Gimeno on 26/5/25.
//

#ifndef COMETA_TRANSFORM_H
#define COMETA_TRANSFORM_H

#define GLM_ENABLE_EXPERIMENTAL
#include <glm.hpp>
#include <gtx/quaternion.hpp>
#include <gtc/matrix_transform.hpp>

class Transform {
public:

    glm::vec3 position = { 0.0f, 0.0f, 0.0f };
    glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };
    glm::vec3 scale = { 1.0f, 1.0f, 1.0f };

private:
    Transform* _parent = nullptr;

public:
    Transform() = default;

    explicit Transform(const glm::vec3& position)
    {
        this->position = position;
        this->rotation = { 0.0f, 0.0f, 0.0f };
        this->scale = { 1.0f, 1.0f, 1.0f };
    }

    Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) : position(position), rotation(rotation), scale(scale) {};

    Transform(const Transform& other)
    {
        position = other.position;
        rotation = other.rotation;
        scale = other.scale;
    };


    [[nodiscard]] glm::mat4 GetTransform() const {
        const glm::mat4 rotation = glm::toMat4(glm::quat(glm::radians(this->rotation)));
        return glm::translate(glm::mat4(1.0f), position) * rotation * glm::scale(glm::mat4(1.0f), scale);
    }

    [[nodiscard]] glm::mat4 GetWorldTransform() const{
        if (_parent != nullptr){
            return _parent->GetWorldTransform() * GetTransform();
        }
        else{
            return GetTransform();
        }
    }

    void SetParent(Transform* newParent){_parent = newParent;}
    [[nodiscard]] Transform* GetParent() const { return _parent; }

    friend std::ostream& operator<<(std::ostream& os, const Transform& transform)
    {
        os << "  - Transform: "
                          << "Pos(" << transform.position.x << ", "
                          << transform.position.y << ", "
                          << transform.position.z << "), "
                          << "Rot(" << transform.rotation.x << ", "
                          << transform.rotation.y << ", "
                          << transform.rotation.z << "), "
                          << "Scale(" << transform.scale.x << ", "
                          << transform.scale.y << ", "
                          << transform.scale.z << ")" << std::endl;
        return os;
    }
};

#endif //COMETA_TRANSFORM_H

