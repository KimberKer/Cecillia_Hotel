//---------------------------------------------------------
// File:    Buffer.cpp
//authors:	Ahmad Mahdi Bin Jamal
// email:	ahmadmahdi.b@digipen.edu
// 
//
// Brief:     Contains the definitions of member functions
//         for the classes VertexBuffer and IndexBuffer.
// 
// Copyright © 2023 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "duckpch.h"
#include "Buffer.h"

#include <glad/glad.h>

namespace Duck {



    // Constructor for VertexBuffer class
    VertexBuffer::VertexBuffer(float* data, size_t size) {

        // Create a vertex buffer object (VBO) and bind it
        glCreateBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);

        // Allocate memory and upload data to the GPU
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);

    }

    // Destructor for VertexBuffer class
    VertexBuffer::~VertexBuffer() {

        // Delete the vertex buffer object (VBO)
        glDeleteBuffers(1, &m_RendererID);

    }

    // Bind the VertexBuffer to the OpenGL context
    void VertexBuffer::Bind() const {

        // Bind the VBO to the GL_ARRAY_BUFFER target
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);

    }

    // Unbind the VertexBuffer from the OpenGL context
    void VertexBuffer::Unbind() const {

        // Unbind the VBO from the GL_ARRAY_BUFFER target (bind to 0)
        glBindBuffer(GL_ARRAY_BUFFER, 0);

    }

    // Constructor for IndexBuffer class
    IndexBuffer::IndexBuffer(const unsigned int* data, size_t count) {

        // Create an index buffer object (IBO) and bind it
        glCreateBuffers(1, &m_RendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);

        // Allocate memory and upload index data to the GPU
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_DYNAMIC_DRAW);

        // Store the count of indices
        m_Count = count;

    }

    // Destructor for IndexBuffer class
    IndexBuffer::~IndexBuffer() {

        // Delete the index buffer object (IBO)
        glDeleteBuffers(1, &m_RendererID);

    }

    // Bind the IndexBuffer to the OpenGL context
    void IndexBuffer::Bind() const {

        // Bind the IBO to the GL_ELEMENT_ARRAY_BUFFER target
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);

    }

    // Unbind the IndexBuffer from the OpenGL context
    void IndexBuffer::Unbind() const {

        // Unbind the IBO from the GL_ELEMENT_ARRAY_BUFFER target (bind to 0)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    }


}