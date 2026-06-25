#pragma once

#include "Core/Base.h"
#include "Core/String.h"

#include "Core/EventSystem.h"

#include <mutex>
#include <unordered_set>

namespace ERUNTIME_NAMESPACE {
    enum class ActionEventType {
        Pressed,
        Released,
    };

    class ActionEvent : public Event {
    public:
        ActionEvent(const String& name, ActionEventType eType)
            : Name(name), Type(eType)
        {
        }

        String Name;
        ActionEventType Type;

        DEFINE_EVENT_TYPE(ActionEvent);
    };

    class ActionSystem {
    public:
        static ActionSystem& Instance();

        // [[nodiscard]]
        // ActionEvent GetActionEvent(const KeyboardEvent& event) const;

        // [[nodiscard]]
        // KeyboardEvent GetKeyboardEvent(const String& name) const;
        
        // void SetAction(KeyboardEvent event, const String& name);

        // bool IsActionPressed(const String& name) const noexcept;
        // bool IsActionReleased(const String& name) const noexcept;

        // void OnTick();

    private:
        ActionSystem() = default;

        std::unordered_set<String> m_ActionSet{};
        std::mutex m_Sync;
    };
}