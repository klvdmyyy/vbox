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
            if(entry.Level == LogLevel::Error || entry.Level == LogLevel::Critical)
                std::println(stderr, "{}:{} [{}:{}] {}", entry.SourceFile, entry.Line, entry.Category, entry.Level, entry.Message);
            else
                std::println("{}:{} [{}:{}] {}", entry.SourceFile, entry.Line, entry.Category, entry.Level, entry.Message);
        }
    };
}