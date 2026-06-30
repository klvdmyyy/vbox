// -*- mode: c++; -*-
#pragma once

#include "Core/Base.h"
#include "Core/Memory.h"
#include "Core/String.h"

#include "Renderer/Shader.h"
#include "Renderer/Context.h"

#include <unordered_map>
#include <type_traits>

namespace ERUNTIME_NAMESPACE {
    class ResourceManager {
    public:
        static ResourceManager& Instance();

        FORCE_INLINE
        inline void SetRendererContext(const Ref<Context>& rendererContext)
        {
            m_rendererContext = rendererContext;
        }

        const Ref<Shader>& LoadShader(const String& filepath);
        const Ref<Shader>& GetShader(const String& filepath) const;
        void ReloadShader(const String& filepath);

    private:
        ResourceManager();

        Ref<Context> m_rendererContext;

        std::unordered_map<String, Ref<Shader>> m_shadersMap;
    };
}