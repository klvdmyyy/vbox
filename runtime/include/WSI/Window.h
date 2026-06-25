#pragma once

#include "Core/String.h"
#include "Core/EventSystem.h"

#include <cstdint>

namespace ERUNTIME_NAMESPACE
{
    using WindowID = std::uint32_t;

    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent(WindowID id)
            : id(id)
        {
        }

        WindowID id;

        DEFINE_EVENT_TYPE(WindowCloseEvent);
    };

    struct WindowSpecification
    {
        std::uint32_t Width;
        std::uint32_t Height;
        String Title;
        bool Resizable = false;
        bool Fullscreen = false;
    };

    class ERUNTIME_API Window
    {
    public:
        virtual ~Window() = default;

        virtual void Update() = 0;
        virtual void* GetWindowHandle() const = 0;

        static Window* Create(const WindowSpecification& spec);
    };
}