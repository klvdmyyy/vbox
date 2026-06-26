#pragma once

#include "Core/Base.h"
#include "Core/String.h"

#include "Core/EventSystem.h"

namespace ERUNTIME_NAMESPACE {
    enum class InputDevice {
        Unknown = 0,

        Keyboard,
    };

    class KeyboardEvent : public Event {
    public:
        KeyboardEvent(uint32_t code, bool pressed = true)
            : k_code(code), k_pressed(pressed)
        {
        }

        const uint32_t k_code;
        const bool k_pressed;

        DEFINE_EVENT_TYPE(KeyboardEvent);
    };

    class Input {
    public:
        static bool IsKeyPressed(uint8_t scancode);
    };
}