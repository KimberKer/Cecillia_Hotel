#include "duckpch.h"
#include "Vertex.h"
#include <glad/glad.h>

namespace Duck {

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

    VertexArray::VertexArray() {

        glCreateVertexArrays(1, &m_RendererID);

    }

    VertexArray::~VertexArray() {

        glDeleteVertexArrays(1, &m_RendererID);

    }


    void VertexArray::Bind() const {

        glBindVertexArray(m_RendererID);
    }

    void VertexArray::Unbind() const {

        glBindVertexArray(0);

    }

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



    void VertexArray::AddIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) {

        glBindVertexArray(m_RendererID);
        indexBuffer->Bind();

        m_IndexBuffer = indexBuffer;

    }

    void VertexArray::SetPrimitiveType(const int32_t primitive) {

        m_PrimitiveType = primitive;
    }

}
