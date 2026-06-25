#pragma once

#include "Core/Base.h"
#include "Core/String.h"

#include <expected>
#include <unordered_map>
#include <functional>
#include <mutex>
#include <vector>

namespace ERUNTIME_NAMESPACE
{
    struct CommandSpecification
    {
        String Name;
        String Description;  
    };

    class ERUNTIME_API CommandArgs
    {
    public:
        [[nodiscard]]
        static CommandArgs Parse(StringView str);

        [[nodiscard]]
        std::size_t Count() const;

    private:
        CommandArgs(const std::vector<StringView>& args);

        std::vector<StringView> m_Args;
    };

    using CommandCallback = std::function<void(const CommandArgs&)>;

    class ERUNTIME_API StringCommandRunner
    {
    public:
        [[nodiscard]]
        static StringCommandRunner& Instance();

        [[nodiscard]]
        std::expected<void, String> Run(StringView cmd);

        [[nodiscard]]
        std::expected<void, String> AddCommand(CommandSpecification cmd, CommandCallback callback);

        [[nodiscard]]
        std::expected<void, String> RemoveCommand(StringView cmd);

        [[nodiscard]]
        std::expected<CommandSpecification, String> GetSpec(StringView cmd) const;

        void Each(std::function<void(const CommandSpecification& spec)>) const;

    private:
        StringCommandRunner() = default;

        std::unordered_map<StringView, CommandCallback> m_CommandMap;
        std::unordered_map<StringView, CommandSpecification> m_CommandSpecMap;
        std::mutex m_Sync;
    };
}