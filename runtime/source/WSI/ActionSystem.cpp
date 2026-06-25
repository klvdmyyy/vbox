#include "WSI/ActionSystem.h"

namespace ERUNTIME_NAMESPACE {
    ActionSystem& ActionSystem::Instance()
    {
        static ActionSystem s_Instance{};
        return s_Instance;
    }
}