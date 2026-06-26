# Создание приложения на Entix Runtime

Для старта нужно создать проект и слинковать его с `entixruntime`

```cmake
project(QuickStartProject)

add_executable(quickstartapp Main.cpp)

target_link_libraries(quickstartapp PRIVATE Entix::Runtime)
```

А в файле `Main.cpp` создать точку входа в приложение Entix Runtime:

```cpp
#include <Core/Application.h>

// For `StdoutLogSink`
#include <Core/Debug/LogSinks.h>

// For `Entix::CreateApplication` entry
#include <Core/EntryPoint.h>

using namespace Entix;

static constexpr auto g_appSpec = ApplicationSpecification {
    .name = "Quick Start App"
    .description = "Example application for Quick Start guide."
    .windowSpec = {
        .width = 800,
        .height = 600,
        .title = "Quick Start"
    },
};

class QuickStartApp : public Application {
public:
    QuickStartApp()
    {
        // Initialize basic logger
        Logger::Instance().AddSink(CreateScope<StdoutLogSink>());
    }
};

// Entix Runtime entry point
Application* Entix::CreateApplication()
{
    return new QuickStartApp();
}

```