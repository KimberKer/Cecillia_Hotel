#pragma once

#include <memory>
#include "Buffer.h"

namespace Duck {

    class VertexArray {
    public:
        VertexArray();
        virtual ~VertexArray();


        void Bind() const;
        void Unbind() const;

         void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
         void AddIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);
         void SetPrimitiveType(const int32_t primitive);

         virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; };
         virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; };
         virtual const int32_t& GetPrimitiveType() const { return m_PrimitiveType; };

    private:
        int32_t m_PrimitiveType{};
        uint32_t m_RendererID{};
        std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;

    };

}