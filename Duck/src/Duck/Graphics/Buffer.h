//---------------------------------------------------------
// File:    Buffer.h
//authors:	Ahmad Mahdi Bin Jamal
// email:	ahmadmahdi.b@digipen.edu
// 
//
// Brief:     Contains the declarations of BufferLayout,
//          VertexBuffer and IndexBuffer. It also contains 
//          the structs ShaderDataTypeSize and Vertex, and 
//          enum class ShadeDataType.
// 
// Copyright © 2023 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once
#include <string>

namespace Duck {

    // Enumeration representing shader data types
    enum class ShaderDataType : uint8_t {
        NONE = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
    };

    // Function to get the size (in bytes) of a ShaderDataType
    static uint32_t ShaderDataTypeSize(ShaderDataType type) {
        switch (type) {
            // Return the size of each data type
        case ShaderDataType::Float:      return 4;
        case ShaderDataType::Float2:     return 4 * 2;
        case ShaderDataType::Float3:     return 4 * 3;
        case ShaderDataType::Float4:     return 4 * 4;
        case ShaderDataType::Mat3:       return 4 * 3 * 3;
        case ShaderDataType::Mat4:       return 4 * 4 * 4;
        case ShaderDataType::Int:        return 4;
        case ShaderDataType::Int2:       return 4 * 2;
        case ShaderDataType::Int3:       return 4 * 3;
        case ShaderDataType::Int4:       return 4 * 4;
        case ShaderDataType::Bool:       return 1;
        }
        return 0;
    }

    // Structure representing elements in a buffer
    struct BufferElements {
        std::string Name;
        ShaderDataType Type;
        uint32_t Offset;
        uint32_t Size;
        bool Normalized;

        // Constructor to initialize BufferElements
        BufferElements(ShaderDataType type, const std::string& name, bool normalized = false)
            : Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized) {
        }

        // Function to get the number of components in the data type
        uint32_t GetComponentCount() const {
            switch (Type) {
                // Return the number of components for each data type
            case ShaderDataType::Float:      return 1;
            case ShaderDataType::Float2:     return 2;
            case ShaderDataType::Float3:     return 3;
            case ShaderDataType::Float4:     return 4;
            case ShaderDataType::Mat3:       return 3;
            case ShaderDataType::Mat4:       return 4;
            case ShaderDataType::Int:        return 1;
            case ShaderDataType::Int2:       return 2;
            case ShaderDataType::Int3:       return 3;
            case ShaderDataType::Int4:       return 4;
            case ShaderDataType::Bool:       return 1;
            }
            return 0;
        }
    };

    // Class representing the layout of a buffer
    class BufferLayout {
    public:
        // Default constructor for BufferLayout
        BufferLayout() {};

        // Constructor for BufferLayout with initializer list of BufferElements
        BufferLayout(const std::initializer_list<BufferElements>& elements)
            : m_Elements(elements) {
            CalculateStrideAndOffset();
        }

        // Function to get the stride (total size) of the buffer layout
        inline uint32_t GetStride() const { return m_stride; }

        // Function to get the elements in the buffer layout
        inline const std::vector<BufferElements>& GetElements() const { return m_Elements; }

        // Iterator functions for accessing elements
        std::vector<BufferElements>::iterator begin() { return m_Elements.begin(); }
        std::vector<BufferElements>::iterator end() { return m_Elements.end(); }
        std::vector<BufferElements>::const_iterator begin() const { return m_Elements.begin(); }
        std::vector<BufferElements>::const_iterator end() const { return m_Elements.end(); }

    private:
        // Calculate stride and offsets for elements in the layout
        void CalculateStrideAndOffset() {
            uint32_t offset = 0;
            m_stride = 0;
            for (auto& element : m_Elements) {
                element.Offset = offset;
                offset += element.Size;
                m_stride += element.Size;
            }
        }

    private:
        std::vector<BufferElements> m_Elements;
        uint32_t m_stride = 0;
    };

    // Class representing a Vertex Buffer
    class VertexBuffer {
    public:
        // Constructor for VertexBuffer
        VertexBuffer(float* data, size_t size);

        // Destructor for VertexBuffer
        virtual ~VertexBuffer();

        // Bind the VertexBuffer to the graphics context
        void Bind() const;

        // Unbind the VertexBuffer from the graphics context
        void Unbind() const;

        // Get the layout of the buffer
        virtual const BufferLayout& GetLayout() const { return m_Layout; }

        // Set the layout of the buffer
        virtual void SetLayout(const BufferLayout& layout) { m_Layout = layout; }

    private:
        unsigned int m_RendererID;
        BufferLayout m_Layout;
    };

    // Class representing an Index Buffer
    class IndexBuffer {
    public:
        // Constructor for IndexBuffer
        IndexBuffer(const unsigned int* data, size_t count);

        // Destructor for IndexBuffer
        virtual ~IndexBuffer();

        // Bind the IndexBuffer to the graphics context
        void Bind() const;

        // Unbind the IndexBuffer from the graphics context
        void Unbind() const;

        // Get the count of indices in the buffer
        inline size_t GetCount() const { return m_Count; }

    private:
        unsigned int m_RendererID;
        size_t m_Count{};
    };

    // Structure representing a Vertex with position, color, and texture coordinates
    struct Vertex {
        float Position[3];
        float Color[4];
        float TexCoords[2];
        float TexID;
    };

}