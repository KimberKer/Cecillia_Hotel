#include "duckpch.h"
#include "Buffer.h"

#include <glad/glad.h>

namespace Duck {



    VertexBuffer::VertexBuffer( float* data, size_t size) {

        glCreateBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    }


    VertexBuffer::~VertexBuffer() {

        glDeleteBuffers(1, &m_RendererID);

    }

    void VertexBuffer::Bind() const {

        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);

    }

    void VertexBuffer::Unbind() const {

        glBindBuffer(GL_ARRAY_BUFFER, 0);

    }




    IndexBuffer::IndexBuffer(const unsigned int* data, size_t count) {

        glCreateBuffers(1, &m_RendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);

        m_Count = count;

    }

    IndexBuffer::~IndexBuffer() {

        glDeleteBuffers(1, &m_RendererID);

    }

    void IndexBuffer::Bind() const {

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);

    }

    void IndexBuffer::Unbind() const {

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    }


}