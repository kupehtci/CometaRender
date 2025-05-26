//
// Created by Daniel Laplana Gimeno on 22/4/25.
//

#include "Mesh.h"

// TODO: Delete this three references

// ------------ CONSTRUCTOR AND DESTRUCTOR ------------

Mesh::Mesh()
{
    _vao = std::make_shared<VertexArray>();
}


// ------------ CUSTOM MESH METHODS ------------

void Mesh::AddVertices(float* vertices, uint32_t numVertices)
{
    _vertices.insert(_vertices.end(), vertices, vertices + numVertices);
    _numVertices += numVertices;
}

void Mesh::AddIndices(uint32_t* indices, uint32_t numIndices)
{
    _indices.insert(_indices.end(), indices, indices + numIndices);
    _numIndices += numIndices;
}


void Mesh::Build()
{
    // std::cout << "################# MESH BUILD METHOD #################" << std::endl;

    // VertexArray vao = VertexArray();
    _vao->CreateVertexBuffer(_vertices.data(), _numVertices * sizeof(float));
    _vao->CreateIndexBuffer(_indices.data(), _numIndices * sizeof(uint32_t));

    // _vao->SetLayoutBuffer({
    //         {0, DataType::Float3, "aPos"},
    //         {1, DataType::Float3, "aNormal"},
    //         {2, DataType::Float3, "aColor"},
    //         {3, DataType::Float2, "aTexCoord"}
    // });
    _vao->GetLayoutBuffer().Bind();

    _vao->Bind();

    // std::cout << "################# END OF MESH BUILD METHOD #################" << std::endl;
}

void Mesh::Draw()
{
    _vao->Bind();
    glDrawElements(GL_TRIANGLES, _numVertices, GL_UNSIGNED_INT, 0);
}


void Mesh::Bind()
{
    _vao->Bind();
}

void Mesh::Unbind()
{
    _vao->Unbind();
}

void Mesh::Debug()
{
    std::cout << "Vertices: " << _numVertices << std::endl;
    for (int i = 0 ; i < _numVertices ; i++)
    {
        std::cout << "Vertex ["<< i << "] : " << _vertices[i] << std::endl;
    }

    std::cout << "Indices: " << _numIndices << std::endl;
    for (int i = 0 ; i < _numIndices ; i++)
    {
        std::cout << "Indices [" << i << "] : " << _indices[i] << std::endl;
    }
}