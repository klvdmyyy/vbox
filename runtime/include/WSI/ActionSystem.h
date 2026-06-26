// -*- mode: c++; -*-
#pragma once

#include "Core/Base.h"
#include "Core/String.h"
#include "Core/Memory.h"

#include "WSI/Input.h"

#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <filesystem>

namespace ERUNTIME_NAMESPACE {
    struct ActionBinding {
        InputDevice device;
        uint8_t scancode;
    };

    class ActionMap {
    public:
        ActionMap() = default;

        void AddAction(const String& name, const ActionBinding& binding);

        [[nodiscard]]
        bool IsPressed(const String& name) const;

        [[nodiscard]]
        static ActionMap LoadFromFile(const std::filesystem::path filepath);
        void SaveToFile(const std::filesystem::path filepath);

    private:
        std::unordered_map<String, ActionBinding> m_bindingMap{};
    };

    class ActionContext {
    public:
        ActionContext(const std::initializer_list<String>& actions)
            : m_actionSet(actions)
        {
        }

        void AddAction(const String& name);

        [[nodiscard]]
        bool HasAction(const String& name) const;

    private:
        std::unordered_set<String> m_actionSet{};
    };
    
    class ActionSystem {
    public:
        static ActionSystem& Instance();

        void PushContext(const ActionContext& context);
        void PopContext();

        void SetActionMap(const ActionMap& map);

        [[nodiscard]]
        bool IsPressed(const String& name) const;

    private:
        ActionMap m_actionMap{};
        std::stack<ActionContext> m_contextStack{};
    };
}