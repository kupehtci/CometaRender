//
// Created by Daniel Laplana Gimeno on 26/5/25.
//

#ifndef COMETA_RENDERABLE_H
#define COMETA_RENDERABLE_H

#include "render/Mesh.h"
#include "render/Material.h"
#include "render/Transform.h"

// Base class for all renderable objects
class Renderable {
protected:
    std::shared_ptr<Mesh> _mesh;
    std::shared_ptr<Material> _material;
    Transform* _transform;

    bool _castShadow = true;

public:
    Renderable(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material, Transform* transform)
        : _mesh(mesh), _material(material), _transform(transform) {}

    virtual ~Renderable() = default;

    // Getters
    std::shared_ptr<Mesh> GetMesh() const { return _mesh; }
    std::shared_ptr<Material> GetMaterial() const { return _material; }
    Transform* GetTransform() const { return _transform; }

    // Setters
    void SetMesh(std::shared_ptr<Mesh> mesh) { _mesh = mesh; }
    void SetMaterial(std::shared_ptr<Material> material) { _material = material; }
    void SetTransform(Transform* transform) { _transform = transform; }

    bool DoesCastShadow() const { return _castShadow; }
    void SetCastShadow(bool value) { _castShadow = value; }
};



#endif //COMETA_RENDERABLE_H
