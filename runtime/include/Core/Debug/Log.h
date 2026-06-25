#pragma once

#include "Core/String.h"
#include "Core/Base.h"
#include "Core/Memory.h"

#include <algorithm>
#include <sstream>
#include <type_traits>
#include <mutex>
#include <format>
#include <vector>
#include <chrono>

#define EX_LOG(LEVEL, CATEGORY, FMT, ...)                               \
    ::ERUNTIME_NAMESPACE::Logger::Instance().Log(::ERUNTIME_NAMESPACE::LogLevel::LEVEL, CATEGORY, \
                                                 std::format(FMT, ##__VA_ARGS__), __FILE__, __LINE__, __FUNCTION__)

namespace ERUNTIME_NAMESPACE
{
    namespace LogCategory
    {
        constexpr auto Core = "Core";
        constexpr auto Renderer = "Renderer";
        constexpr auto Driver = "Driver";
    }

    enum class LogLevel
        {
            Trace = 0,
            Info,
            Warning,
            Error,
            Critical,
        };

    [[nodiscard]]
    const StringView LogLevelToString(const LogLevel& level);

    struct LogEntry
    {
        LogLevel Level;
        const char *Category;
        StringView Message;
        const char *SourceFile;
        int Line;
        const char *FunctionSignature;
    };

    class ERUNTIME_API LogSink
        {
        public:
        LogSink() = default;
        virtual ~LogSink() = default;

        virtual void Write(const LogEntry &item) = 0;
        };

    class ERUNTIME_API Logger
        {
        public:
        static Logger &Instance();
      
        void AddSink(Scope<LogSink> sink);

        void Log(LogLevel level, const char *category, StringView message,
                 const char *sourceFile, int line, const char *functionSignature);

        private:
        std::vector<Scope<LogSink>> m_Sinks;
        std::mutex m_Sync;
        };
}

template<>
struct std::formatter<ERUNTIME_NAMESPACE::LogLevel, char>
{
    template<class ParseContext>
    constexpr ParseContext::iterator parse(ParseContext& ctx)
    {
        auto it = ctx.begin();
        return it;
    }

    template<typename FmtContext>
    FmtContext::iterator format(ERUNTIME_NAMESPACE::LogLevel level,
                                FmtContext &ctx) const
    {
        std::ostringstream out;
        out << ERUNTIME_NAMESPACE::LogLevelToString(level);

        return std::ranges::copy(std::move(out).str(), ctx.out()).out;
    }
};
