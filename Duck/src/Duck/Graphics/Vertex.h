//---------------------------------------------------------
// File:    Vertex.h
//authors:	Ahmad Mahdi Bin Jamal
// email:	ahmadmahdi.b@digipen.edu
// 
//
// Brief:	This header file defines the VertexArray class, 
//          which represents a vertex array object in OpenGL. 
//          It provides functionality for managing vertex and 
//          index buffers within a vertex array, as well as 
//          specifying the primitive type for rendering.
// 
// 
// Copyright © 2023 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once

#include <memory>
#include "Buffer.h"

namespace Duck {

    class VertexArray {

    public:
        VertexArray();                          // Constructor: Create a vertex array.
        virtual ~VertexArray();                 // Destructor: Clean up the vertex array.

        void Bind() const;                      // Bind the vertex array for rendering.
        void Unbind() const;                    // Unbind any active vertex array.

        void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);  // Add a vertex buffer to the vertex array.
        void AddIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);     // Add an index buffer to the vertex array.
        void SetPrimitiveType(const int32_t primitive);                           // Set the primitive type for rendering.

        virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; };
        virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; };
        virtual const int32_t& GetPrimitiveType() const { return m_PrimitiveType; };

    private:
        int32_t m_PrimitiveType{};                  // The primitive type for rendering (e.g., GL_TRIANGLES).
        uint32_t m_RendererID{};                    // The OpenGL ID for the vertex array object.
        std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;  // List of vertex buffers.
        std::shared_ptr<IndexBuffer> m_IndexBuffer;  // Index buffer associated with the vertex array.

    };

}