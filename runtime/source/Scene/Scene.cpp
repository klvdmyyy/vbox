#include "Scene/Scene.h"

#include "Scene/Entity.h"

namespace ERUNTIME_NAMESPACE {
    Scene::Scene()
    {
    }

    Scene::~Scene()
    {
    }

    Entity Scene::CreateEntity(const String& name)
    {
        return CreateEntityWithUUID(UUID(), name);
    }

    Entity Scene::CreateEntityWithUUID(UUID uuid, const String& name)
    {
        Entity entity = { m_registry.create(), this };
        // entity.AddComponent<IDComponent>(uuid);
        // entity.AddComponent<TransformComponent>();
        // auto& tag = entity.AddComponent<TagComponent>();
        // tag.name = name.empty() ? "Entity" : name;

        // m_entityMap[uuid] = entity;

        return entity;        
    }

    void Scene::OnTick(float deltaTime)
    {
    }
}