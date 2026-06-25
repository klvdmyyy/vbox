#include "Drivers/OpenGL/OpenGLVertexArray.h"

#include "Drivers/OpenGL/OpenGLContext.h"

namespace ERUNTIME_NAMESPACE {

    static GLenum ShaderDataTypeToGLenum(ShaderDataType type)
    {
        switch (type) {
        case ShaderDataType::Bool:
            return GL_BOOL;
        case ShaderDataType::Int:
            return GL_INT;
        case ShaderDataType::Int2:
            return GL_INT;
        case ShaderDataType::Int3:
            return GL_INT;
        case ShaderDataType::Int4:
            return GL_INT;
        case ShaderDataType::Float:
            return GL_FLOAT;
        case ShaderDataType::Float2:
            return GL_FLOAT;
        case ShaderDataType::Float3:
            return GL_FLOAT;
        case ShaderDataType::Float4:
            return GL_FLOAT;
        case ShaderDataType::Mat3:
            return GL_FLOAT;
        case ShaderDataType::Mat4:
            return GL_FLOAT;
        default:
            break;
        }

        EX_ASSERT(false, "Unknown ShaderDataType: {}", static_cast<int>(type));
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray()
    {
        glCreateVertexArrays(1, &m_VAO);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    { glDeleteVertexArrays(1, &m_VAO);
    }

    void OpenGLVertexArray::Bind() const
    { glBindVertexArray(m_VAO);
    }

    void OpenGLVertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
    {
      EX_ASSERT(vertexBuffer->GetLayout().GetElements().size(),
              "vertex buffer has no layout!");

        this->Bind();

        vertexBuffer->Bind();

        uint32_t index = 0;
        const auto &layout = vertexBuffer->GetLayout();

        for(const auto& element : layout)
        {
            glEnableVertexAttribArray(index);
          glVertexAttribPointer(index, element.GetComponentCount(),
                                ShaderDataTypeToGLenum(element.Type),
                                element.Normalized ? GL_TRUE : GL_FALSE,
                                layout.GetStride(),
                                reinterpret_cast<const void *>(element.Offset));
            index++;
        }

        m_VertexBuffers.push_back(vertexBuffer);

        vertexBuffer->Unbind();

        this->Unbind();
    }

    void
    OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer> &indexBuffer)
    {
        this->Bind();

        indexBuffer->Bind();

        m_IndexBuffer = indexBuffer;

        this->Unbind();

        indexBuffer->Unbind();
    }
 }