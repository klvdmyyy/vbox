#pragma once

#include "WSI/Window.h"

#include <SDL3/SDL.h>

namespace ERUNTIME_NAMESPACE
{
    class ERUNTIME_API WindowSDL : public Window
    {
    public:
        WindowSDL(const WindowSpecification& spec);
        ~WindowSDL();

        void Update() final;
        
        void* GetWindowHandle() const final
        {
            return static_cast<void*>(m_Window);
        }

    private:
        SDL_Window* m_Window;
    };
}