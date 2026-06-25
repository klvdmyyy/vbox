// -*- mode: c++; -*-
#pragma once

#include "Core/String.h"
#include "Core/Memory.h"
#include "Core/EventSystem.h"

#include "Core/Debug/Log.h"
#include "Core/StringCommandRunner.h"

#include "WSI/Window.h"

#include "Renderer/Context.h"

namespace ERUNTIME_NAMESPACE
{
    struct ApplicationSpecification
    {
        String name;
        String description;
        WindowSpecification windowSpec;
    };

    class ERUNTIME_API Application : EventListener
    {
    public:
        ~Application();

        static Application& Instance() { return *s_instance; }

        void Run(int argc, char** argv);

        void OnEvent(const Event& event) final;

        ApplicationSpecification GetSpec() const noexcept { return k_spec; }
        Window& GetWindow() const noexcept { return *m_window; }
        Context& GetContext() const noexcept { return *m_context; }

    protected:
        Application(const ApplicationSpecification& spec);

    private:
        static Application* s_instance;

        const ApplicationSpecification k_spec;

        Ref<Window> m_window;
        Ref<Context> m_context;

        bool m_running;
    };
}