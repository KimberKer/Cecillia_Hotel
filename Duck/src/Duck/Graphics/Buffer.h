#pragma once
#include <string>

namespace Duck {

    enum class ShaderDataType : uint8_t {

        NONE = 0, Float, Float2, Float3, Float4, Mat3, Mat4,Int, Int2, Int3, Int4, Bool 

    };

    static uint32_t ShaderDataTypeSize(ShaderDataType type) {


            switch (type) {

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

    struct BufferElements {

        std::string Name;
        ShaderDataType Type;
        uint32_t  Offset;
        uint32_t    Size;
        bool Normalized;

        // BufferElements(){};

        BufferElements( ShaderDataType type, const std::string& name, bool normalized = false) 
            : Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized) {

        }


        uint32_t GetComponentCount() const {


            switch (Type) {

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

    class BufferLayout {

    public:

        BufferLayout() {};

        BufferLayout(const std::initializer_list<BufferElements>& elements)
        : m_Elements(elements){

            CalculateStrideAndOffset();
        
        }

        inline uint32_t GetStride() const { return m_stride; };
        inline const std::vector<BufferElements>& GetElements() const { return m_Elements; }

        std::vector<BufferElements>::iterator begin() { return m_Elements.begin(); };
        std::vector<BufferElements>::iterator end() { return m_Elements.end(); };
        std::vector<BufferElements>::const_iterator begin() const { return m_Elements.begin(); };
        std::vector<BufferElements>::const_iterator end() const { return m_Elements.end(); };

    private:
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

    class VertexBuffer {
    public:
        VertexBuffer( float* data, size_t size);
        virtual ~VertexBuffer();


        void Bind() const;
        void Unbind() const;

        virtual const BufferLayout& GetLayout() const { return m_Layout; };
        virtual void SetLayout(const BufferLayout& layout) { m_Layout = layout; };

    private:

        unsigned int m_RendererID;
        BufferLayout m_Layout;
    };


    class IndexBuffer {
    public:

        IndexBuffer(const unsigned int* data, size_t count);
        virtual ~IndexBuffer();

        void Bind() const;
        void Unbind() const;

        inline size_t GetCount() const { return m_Count; }

    private:

        unsigned int m_RendererID;
        size_t m_Count{};

    };


    

}