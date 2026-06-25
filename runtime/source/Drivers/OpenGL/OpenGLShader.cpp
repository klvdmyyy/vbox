#include "Drivers/OpenGL/OpenGLShader.h"

#include "Core/Assert.h"
#include "Core/File.h"

#include <tracy/Tracy.hpp>

#include <vector>

namespace ERUNTIME_NAMESPACE
{
    static GLenum ShaderStageToGLenum(ShaderStage stage) {
      switch (stage) {
      case ShaderStage::Vertex:
        return GL_VERTEX_SHADER;
      case ShaderStage::Fragment:
        return GL_FRAGMENT_SHADER;
      }

      EX_ASSERT(false, "Unknown shader stage!");
    }

    static GLuint CompileOpenGLShader(const std::string &src,
                                        GLenum shader_type) {
      ZoneScoped;
      GLuint shader = glCreateShader(shader_type);

      const GLchar *source = static_cast<const GLchar *>(src.c_str());
      glShaderSource(shader, 1, &source, 0);

      glCompileShader(shader);

      GLint isCompiled = 0;
      glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
      if (isCompiled == GL_FALSE) {
        GLint maxLenght = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLenght);

        std::vector<GLchar> infoLog(maxLenght);
        glGetShaderInfoLog(shader, maxLenght, &maxLenght, &infoLog[0]);

        glDeleteShader(shader);

        EX_ASSERT(false, "failed to compile shader. error: {}", infoLog.data());

        /* TODO: Error log + Assertion!!!!!! Failed to compile shader. Info message
         * in `info_log` variable */
      }

      return shader;
    }

    OpenGLShader::OpenGLShader(const String& filepath)
    {
      ZoneScoped;
        auto source = File(filepath).ReadStr();

        auto shaderSourceMap = GLSL_Preprocess(source);

        auto &vertexSource = shaderSourceMap[ShaderStage::Vertex];
        auto &fragmentSource = shaderSourceMap[ShaderStage::Fragment];

        auto vertShader = CompileOpenGLShader(vertexSource, GL_VERTEX_SHADER);
        auto fragShader =
            CompileOpenGLShader(fragmentSource, GL_FRAGMENT_SHADER);

        m_Program = glCreateProgram();

        glAttachShader(m_Program, vertShader);
        glAttachShader(m_Program, fragShader);
        glLinkProgram(m_Program);

        GLint isLinked = 0;
        glGetProgramiv(m_Program, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLenght = 0;
          glGetProgramiv(m_Program, GL_INFO_LOG_LENGTH, &maxLenght);

            std::vector<GLchar> infoLog(maxLenght);
          glGetProgramInfoLog(m_Program, maxLenght, &maxLenght, &infoLog[0]);

            glDeleteProgram(m_Program);
            glDeleteShader(vertShader);
            glDeleteShader(fragShader);

            EX_ASSERT(false, "failed to link shader program. error: {}",
                    infoLog.data());

            /* TODO: Error log + Assertion!!!!!! Failed to link program. Info message in `info_log` variable */
        }

        glDetachShader(m_Program, vertShader);
        glDetachShader(m_Program, fragShader);
    }

    OpenGLShader::~OpenGLShader()
    { glDeleteProgram(m_Program);
    }

    void OpenGLShader::Bind() const
    { glUseProgram(m_Program);
    }

    void OpenGLShader::Unbind() const
    {
        glUseProgram(0);
    }
}