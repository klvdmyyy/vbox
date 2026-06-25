#pragma once

#include "Core/Base.h"

#include "Core/String.h"

namespace ERUNTIME_NAMESPACE {
    enum class InputDevice {
        Unknown = 0,

        Keyboard,
    };

    namespace Input {
        bool GetAction(const String& name);
    }
}