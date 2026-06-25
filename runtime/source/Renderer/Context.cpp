#include "Renderer/Context.h"

#include "Drivers/OpenGL/OpenGLContext.h"

namespace ERUNTIME_NAMESPACE
{
    Context* Context::Create(const Ref<Window> &window)
    {
        return new OpenGLContext(window);
    }
}