#pragma once

#include "Core/Base.h"

#include "Renderer/Buffer.h"

#include <glad/glad.h>

namespace ERUNTIME_NAMESPACE
{
    class ERUNTIME_API OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* data, uint32_t size);
        ~OpenGLVertexBuffer();

        void Bind() const final;
        void Unbind() const final;

        const BufferLayout &GetLayout() const noexcept final {
          return m_Layout;
        }
        void SetLayout(const BufferLayout &layout) final { m_Layout = layout; }

    private:
        GLuint m_VBO;
        BufferLayout m_Layout;
    };

    class ERUNTIME_API OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
        ~OpenGLIndexBuffer();

        void Bind() const final;
        void Unbind() const final;

        uint32_t GetCount() const final { return m_Count; }
    
    private:
        GLuint m_EBO;
        uint32_t m_Count;
    };
}