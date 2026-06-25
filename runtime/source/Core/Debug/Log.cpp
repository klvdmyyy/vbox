#include "Core/Debug/Log.h"

#include "Core/Assert.h"

#include <filesystem>

namespace fs = std::filesystem;

namespace ERUNTIME_NAMESPACE {
    const StringView LogLevelToString(const LogLevel& level)
    {
#define ADD_LEVEL(X) case ::ERUNTIME_NAMESPACE::LogLevel::X: return #X
        switch(level)
            {
                ADD_LEVEL(Trace);
                ADD_LEVEL(Info);
                ADD_LEVEL(Warning);
                ADD_LEVEL(Error);
                ADD_LEVEL(Critical);
            }
#undef ADD_LEVEL

        EX_ASSERT(false, "Unknown log level provided: {}", static_cast<int>(level));
    }

    Logger& Logger::Instance()
    {
        static Logger s_logger;
        return s_logger;
    }

    void Logger::AddSink(Scope<LogSink> sink) {
        m_sinks.push_back(std::move(sink));
    }

    void Logger::Log(LogLevel level, const char *category, StringView message,
                     std::optional<const char *> sourceFile,
                     std::optional<int> line,
                     std::optional<const char *> functionSignature) {
        for (auto& sink : m_sinks) {
            sink->Write(LogEntry{.level = level,
                                 .category = category,
                                 .message = message,
                                 .sourceFile = sourceFile.has_value() ? std::optional(fs::relative(sourceFile.value(), EX_PROJECT_ROOT).c_str()) : std::nullopt,
                                 .line = line,
                                 .functionSignature = functionSignature});
        }
    }
}