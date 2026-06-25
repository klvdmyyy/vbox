#include <Core/Application.h>

#include <Core/Debug/Log.h>
#include <Core/Debug/LogSinks.h>

using namespace ERUNTIME_NAMESPACE;

int main(int argc, char** argv)
{
    ApplicationSpecification spec = {
        .Name = "VBox Game",
        .Description = "Voxel Sandbox Game",
        .WindowSpec = {
            .Width = 800,
            .Height = 600,
            .Title = "VBox Game"
        },
    };

    Logger::Instance().AddSink(CreateScope<StdoutLogSink>());

    // Just print log message
    // Debug::Log(LogLevel::Info, LogCategory::Core, "Hello, {}!", "World");

    // Print log message with additional information (source file, line, function signature)
    EX_LOG(Trace, LogCategory::Core, "Hello, World!");

    return Application(spec).Run(argc, argv);
}