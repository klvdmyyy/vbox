#include "Drivers/OpenGL/OpenGLContext.h"

#include "Core/Assert.h"

#include "Drivers/OpenGL/OpenGLBuffer.h"
#include "Drivers/OpenGL/OpenGLShader.h"
#include "Drivers/OpenGL/OpenGLVertexArray.h"

#include <tracy/TracyOpenGL.hpp>

namespace ERUNTIME_NAMESPACE {
    OpenGLContext::OpenGLContext(const Ref<Window>& window)
        : m_Window(window)
    {
        m_Context = SDL_GL_CreateContext(static_cast<SDL_Window*>(m_Window->GetWindowHandle()));

        EX_ASSERT(m_Context, "failed to create opengl context. sdl error: {}", SDL_GetError());

        SDL_GL_MakeCurrent(static_cast<SDL_Window*>(m_Window->GetWindowHandle()), m_Context);

        EX_ASSERT(gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress), "failed to load opengl loader!");
    }

    OpenGLContext::~OpenGLContext()
    {
        SDL_GL_DestroyContext(m_Context);
    }

    void OpenGLContext::SetClearColor(float r, float g, float b)
    {
        glClearColor(r, g, b, 1.0f);
    }

    void OpenGLContext::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void OpenGLContext::Swap()
    {
        SDL_GL_SwapWindow(static_cast<SDL_Window*>(m_Window->GetWindowHandle()));
    }

    void OpenGLContext::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray)
    {
        shader->Bind();
      vertexArray->Bind();
        glDrawElements(GL_TRIANGLES,
                       vertexArray->GetIndexBuffer()->GetCount(),
                       GL_UNSIGNED_INT, 0);
    }


    [[nodiscard]]
    VertexArray* OpenGLContext::CreateVertexArray()
    {
        return new OpenGLVertexArray();
    }
    
    [[nodiscard]]
    Shader* OpenGLContext::CreateShader(const String& filepath)
    {
        return new OpenGLShader(filepath);
    }

    [[nodiscard]]
    VertexBuffer* OpenGLContext::CreateVertexBuffer(float* data, uint32_t size)
    {
        return new OpenGLVertexBuffer(data, size);
    }

    [[nodiscard]]
    IndexBuffer* OpenGLContext::CreateIndexBuffer(uint32_t* indices, uint32_t count)
    {
        return new OpenGLIndexBuffer(indices, count);
    }
}