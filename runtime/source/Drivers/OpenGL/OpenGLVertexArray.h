#pragma once

#include "Core/Base.h"

#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"

#include <glad/glad.h>

namespace ERUNTIME_NAMESPACE
{
    class ERUNTIME_API OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray();

        void Bind() const final;
        void Unbind() const final;

        void AddVertexBuffer(const Ref<VertexBuffer>& vertex_buffer) final;
        void SetIndexBuffer(const Ref<IndexBuffer>& index_buffer) final;

        [[nodiscard]]
        const std::vector<Ref<VertexBuffer>> &GetVertexBuffers() const final {
          return m_VertexBuffers;
        }
        const Ref<IndexBuffer> &GetIndexBuffer() const final {
          return m_IndexBuffer;
        }

    private:
        GLuint m_VAO;

        std::vector<Ref<VertexBuffer>> m_VertexBuffers;
        Ref<IndexBuffer> m_IndexBuffer;
    };
}