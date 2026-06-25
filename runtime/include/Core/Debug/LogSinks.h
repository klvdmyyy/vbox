#pragma once

#include "Core/Debug/Log.h"

#include <print>

namespace ERUNTIME_NAMESPACE
{
    class StdoutLogSink : public LogSink
    {
    public:
        inline void Write(const LogEntry& entry) final
        {
            if(entry.level == LogLevel::Error || entry.level == LogLevel::Critical)
                std::println(stderr, "{}{}{}[{}:{}] {}",
                             entry.sourceFile.has_value() ? std::format("{}:", entry.sourceFile.value()) : "",
                             entry.line.has_value() ? std::format("{} ", entry.line.value()) : "",
                             entry.functionSignature.has_value() ? std::format("(in {}) ", entry.functionSignature.value()) : "",
                             entry.category,
                             entry.level,
                             entry.message);
            else
                std::println("{}{}{}[{}:{}] {}",
                             entry.sourceFile.has_value() ? std::format("{}:", entry.sourceFile.value()) : "",
                             entry.line.has_value() ? std::format("{} ", entry.line.value()) : "",
                             entry.functionSignature.has_value() ? std::format("(in {}) ", entry.functionSignature.value()) : "",
                             entry.category,
                             entry.level,
                             entry.message);
        }
    };
}