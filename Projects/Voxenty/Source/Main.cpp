#define GAME_MAIN
#include <GameFramework.h>

static const Entix::ApplicationSpecification g_spec = {
    .name = "Voxenty",
    .description = "Simple Minecraft-like Game",
    .windowSpec = {
        .width = 800,
        .height = 600,
        .title = "Voxenty 1.0",
        .resizable = false,
    },
};

class Voxenty : public Application
{
public:
    Voxenty() : Application(g_spec)
    {
    }

    void OnInit() final
    {
    }
};

Application* Entix::CreateApplication()
{
    return new Voxenty();
}