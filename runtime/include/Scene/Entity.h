// -*- mode: c++; -*-
#pragma once

#include "Core/Base.h"
#include "Core/TypeName.h"
#include "Core/Assert.h"

#include "Scene/Scene.h"

#include <entt/entt.hpp>

namespace ERUNTIME_NAMESPACE {

    class Entity {
    public:
        Entity(const Entity& other) = default;
        
        template<typename T, typename... Args>
        T& AddComponent(Args&&... args)
        {
            EX_ASSERT(!HasComponent<T>(), "Entity already has component '{}'", TypeName<T>());

            T& component = m_scene->m_registry.emplace<T>(m_entityHandle, std::forward<Args>(args)...);
            return component;
        }

        template<typename T>
        bool HasComponent()
        {
            return false;
        }

    private:
        friend Scene;

        Entity(entt::entity handle, Scene* scene) {}
        
        entt::entity m_entityHandle{entt::null};
        Scene* m_scene;
    };
}