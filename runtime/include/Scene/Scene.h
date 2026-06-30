// -*- mode: c++; -*-
#pragma once

#include "Core/Base.h"
#include "Core/Types.h"
#include "Core/String.h"

#include <entt/entt.hpp>

namespace ERUNTIME_NAMESPACE {
    class Entity;

    class Scene {
    public:
        Scene();
        ~Scene();

        Entity CreateEntity(const String& name = String());
        Entity CreateEntityWithUUID(UUID uuid, const String& name = String());
        void DestroyEntity(Entity entity);

        void OnTick(float deltaTime);

    private:
        friend class Entity;

        entt::registry m_registry;
    };
}