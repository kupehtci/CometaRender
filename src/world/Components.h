#ifndef COMETA_COMPONENTS_H
#define COMETA_COMPONENTS_H

#include <iostream>
#include <string>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm.hpp>
#include <gtx/quaternion.hpp>
#include <gtc/matrix_transform.hpp>
#include <utility>

#include "render/Texture.h"
#include "render/Mesh.h"
#include "render/Material.h"

class Entity;

/**
 * Component virtual class
 */
class Component {
private:
	Entity* _owner = nullptr;

public:
	virtual ~Component() = default;

	// ------------ GETTERS AND SETTERS ------------
	[[nodiscard]] Entity* GetOwner() const { return _owner; }
	void SetOwner(Entity* newOwner) { _owner = newOwner; }

	friend class Entity;
	friend class ComponentRegistry;
};

class Transform : public Component {
public: 

	glm::vec3 position = { 0.0f, 0.0f, 0.0f }; 
	glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };
	glm::vec3 scale = { 1.0f, 1.0f, 1.0f }; 

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
		const glm::mat4 rotation = glm::toMat4(glm::quat(this->rotation));
		return glm::translate(glm::mat4(1.0f), position) * rotation * glm::scale(glm::mat4(1.0f), scale);
	}

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

class MeshRenderable : public Component {
private:
	std::shared_ptr<Mesh> _mesh = nullptr;
	std::shared_ptr<Material> _material = nullptr;

public:
	MeshRenderable() = default;
	MeshRenderable(const MeshRenderable&) = default;

	// Properties management methods

	void SetMesh(const std::shared_ptr<Mesh>& mesh) { _mesh = mesh; }
	void SetMaterial(const std::shared_ptr<Material>& material) {_material = material;}

	// ------------ GETTERS ------------
	[[nodiscard]] std::shared_ptr<Mesh> GetMesh() const { return _mesh; }
	[[nodiscard]] std::shared_ptr<Material> GetMaterial() const { return _material; }
};


class SpriteRenderable : public Component {
public: 
	Texture texture; 
	glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

	SpriteRenderable() = default;
	SpriteRenderable(const SpriteRenderable&) = default;
};


class Collider : public Component {
public: 
	Collider() = default;
	Collider(const Collider&) = default;
};

class RigidBody : public Component
{
public:
	glm::vec3 linearVelocity = { 0.0f, 0.0f, 0.0f };
	glm::vec3 angularVelocity = { 0.0f, 0.0f, 0.0f };
	float mass = 1.0f;

	RigidBody() = default;
};

class Tag : public Component {
private: 
	std::string _tag = ""; 
public: 
	Tag() = default;
	Tag(const Tag&) = default;
	explicit Tag(std::string  tag) : _tag(std::move(tag)) {}

	std::string GetTag() { return _tag;  }
	void SetTag(const std::string& tag) { _tag = tag; }
};

#endif