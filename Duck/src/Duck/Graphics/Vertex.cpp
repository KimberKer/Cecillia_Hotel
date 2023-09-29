//---------------------------------------------------------
// File:    Vertex.cpp
//authors:	Ahmad Mahdi Bin Jamal
// email:	ahmadmahdi.b@digipen.edu
// 
//
// Brief:	This source file contains the implementation of 
//          the VertexArray class and helper functions related 
//          to OpenGL vertex attributes and types.
// 
// 
// Copyright © 2023 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "duckpch.h"
#include "Vertex.h"
#include <glad/glad.h>

namespace Duck {


    // Helper function to map ShaderDataType to OpenGL data types.
    GLenum ShaderTypeToOpenGLType(ShaderDataType type) {

        switch (type) {

        case ShaderDataType::Float:      return GL_FLOAT;
        case ShaderDataType::Float2:     return GL_FLOAT;
        case ShaderDataType::Float3:     return GL_FLOAT;
        case ShaderDataType::Float4:     return GL_FLOAT;
        case ShaderDataType::Mat3:       return GL_FLOAT;
        case ShaderDataType::Mat4:       return GL_FLOAT;
        case ShaderDataType::Int:        return GL_INT;
        case ShaderDataType::Int2:       return GL_INT;
        case ShaderDataType::Int3:       return GL_INT;
        case ShaderDataType::Int4:       return GL_INT;
        case ShaderDataType::Bool:       return GL_BOOL;

        }

        return 0;

    }

    // VertexArray constructor: Create a vertex array object.
    VertexArray::VertexArray() {

        glCreateVertexArrays(1, &m_RendererID);

    }

    // VertexArray destructor : Clean up the vertex array object.
    VertexArray::~VertexArray() {

        glDeleteVertexArrays(1, &m_RendererID);

    }

    // Bind the vertex array for rendering.
    void VertexArray::Bind() const {

        glBindVertexArray(m_RendererID);
    }

    // Unbind any active vertex array.
    void VertexArray::Unbind() const {

        glBindVertexArray(0);

    }

    // Add a vertex buffer to the vertex array.
    void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) {

        glBindVertexArray(m_RendererID);
        vertexBuffer->Bind();
        uint32_t Index = 0;
        const auto& layout = vertexBuffer->GetLayout();

        for (const auto& element : layout) {

            glEnableVertexAttribArray(Index);
            glVertexAttribPointer(Index, element.GetComponentCount(), ShaderTypeToOpenGLType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.Offset);
            Index++;

        }

        m_VertexBuffers.push_back(vertexBuffer);

    }

    // Add an index buffer to the vertex array.
    void VertexArray::AddIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) {

        glBindVertexArray(m_RendererID);
        indexBuffer->Bind();

        m_IndexBuffer = indexBuffer;

    }

    // Set the primitive type for rendering(e.g., GL_TRIANGLES, GL_LINES).
    void VertexArray::SetPrimitiveType(const int32_t primitive) {

        m_PrimitiveType = primitive;
    }

}
