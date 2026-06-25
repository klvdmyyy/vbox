#pragma once

#include "Core/Assert.h"
#include "Core/Base.h"
#include "Core/String.h"

#include <vector>

namespace ERUNTIME_NAMESPACE
{
    enum class ShaderDataType {
        None = 0,
        Bool,
        Int,
        Int2,
        Int3,
        Int4,
        Float,
        Float2,
        Float3,
        Float4,
        Mat3,
        Mat4
    };

    [[nodiscard]]
    static uint32_t ShaderDataTypeSize(ShaderDataType type)
    {
        switch (type) {
        case ShaderDataType::None:
            return 0;
        case ShaderDataType::Bool:
            return 1;
        case ShaderDataType::Int:
            return 4;
        case ShaderDataType::Int2:
            return 4 * 2;
        case ShaderDataType::Int3:
            return 4 * 3;
        case ShaderDataType::Int4:
            return 4 * 4;
        case ShaderDataType::Float:
            return 4;
        case ShaderDataType::Float2:
            return 4 * 2;
        case ShaderDataType::Float3:
            return 4 * 3;
        case ShaderDataType::Float4:
            return 4 * 4;
        case ShaderDataType::Mat3:
            return 4 * 3 * 3;
        case ShaderDataType::Mat4:
            return 4 * 4 * 4;
        }

        EX_ASSERT(false, "Unknown ShaderDataType: {}", static_cast<int>(type));
        return 0;
    }

    struct ERUNTIME_API BufferElement
    {
        String Name;
        ShaderDataType Type;
        uint32_t Size;
        size_t Offset;
        bool Normalized;

        BufferElement(const String& name, ShaderDataType type, bool normalized = false)
            : Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0),
              Normalized(normalized)
        {
        }

        [[nodiscard]]
        uint32_t GetComponentCount() const
        {
            switch (Type) {
            case ShaderDataType::None:
                return 0;
            case ShaderDataType::Bool:
                return 1;
            case ShaderDataType::Int:
                return 1;
            case ShaderDataType::Int2:
                return 2;
            case ShaderDataType::Int3:
                return 3;
            case ShaderDataType::Int4:
                return 4;
            case ShaderDataType::Float:
                return 1;
            case ShaderDataType::Float2:
                return 2;
            case ShaderDataType::Float3:
                return 3;
            case ShaderDataType::Float4:
                return 4;
            case ShaderDataType::Mat3:
                return 3 * 3;
            case ShaderDataType::Mat4:
                return 4 * 4;
            }

            EX_ASSERT(false, "Unknown ShaderDataType: {}", static_cast<int>(Type));
            return 0;
        }
    };

    class ERUNTIME_API BufferLayout
    {
    public:
        BufferLayout() { }
        BufferLayout(const std::initializer_list<BufferElement>& elements)
            : m_Elements(elements)
        {
            CalculateOffsetAndStride();
        }

        [[nodiscard]]
        uint32_t GetStride() const noexcept
        {
            return m_Stride;
        }

        const std::vector<BufferElement> &GetElements() const {
          return m_Elements;
        }

        std::vector<BufferElement>::iterator begin() {
          return m_Elements.begin();
        }
        std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
        std::vector<BufferElement>::const_iterator begin() const {
          return m_Elements.begin();
        }
        std::vector<BufferElement>::const_iterator end() const {
          return m_Elements.end();
        }

    private:
        void CalculateOffsetAndStride()
        {
            uint32_t offset = 0;
            m_Stride = 0;
            for(auto& element : m_Elements)
            {
                element.Offset = offset;
                offset += element.Size;
                m_Stride += element.Size;
            }
        }

        std::vector<BufferElement> m_Elements;
        uint32_t m_Stride = 0;
    };

    class ERUNTIME_API VertexBuffer
    {
    public:
        virtual ~VertexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        [[nodiscard]]
        virtual const BufferLayout &GetLayout() const = 0;

        virtual void SetLayout(const BufferLayout& layout) = 0;
    };

    class ERUNTIME_API IndexBuffer
    {
    public:
        virtual ~IndexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        [[nodiscard]]
        virtual uint32_t GetCount() const = 0;
    };
}