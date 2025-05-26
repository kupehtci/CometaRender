#pragma once

#ifndef AURAGL_BUFFER_H
#define AURAGL_BUFFER_H

#include <cstdint>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "debug/Assertion.h"
#include "./DataType.h"



/**
* Buffer abstract class that define the minimal structure of a Renderer API Buffer
*/
class Buffer {
protected:
	uint32_t _uid = 0;
	bool _empty = true;
public:
	virtual ~Buffer() = default;
	/**
	* Bind the buffer to the active one
	*/
	virtual void Bind() = 0;
	virtual void Unbind() = 0;


	// --------- GETTERS ---------- // 
	[[nodiscard]] inline uint32_t GetUid() const { return _uid; }
};

/**
	Vertex Buffer that contains vertices data
*/
class VertexBuffer : public Buffer{

private:
	// LayoutBuffer _layoutBuffer;

public:
	VertexBuffer();

	VertexBuffer(uint32_t size); 

	/**
	* Create a Vertex Buffer with the specified array of vertices and size
	* Data is defined so will be set to Static drawing because data won't change
	*/
	VertexBuffer(float* vertices, uint32_t size);
	~VertexBuffer() final;

	void Bind() override; 
	void Unbind() override;
	// LayoutBuffer& GetLayoutBuffer() { return _layoutBuffer; }
	// void SetLayoutBuffer(const LayoutBuffer& layoutBuffer) { _layoutBuffer = layoutBuffer; }
};

/**
* Indexes Buffer that contains Indices information for Elements Buffers
*/
class IndexBuffer : public Buffer{

private:
	uint32_t _count; 

public:
	IndexBuffer(); 
	IndexBuffer(uint32_t* indices, uint32_t size);
	~IndexBuffer() final;

	void Bind() override;
	void Unbind() override;

	// ---------- GETTERS ---------- //
	inline uint32_t GetCount() { return _count;  }
};

#endif  //AURAGL_BUFFER_H