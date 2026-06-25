#include "Core/StringCommandRunner.h"

#include <cctype>
#include <format>

namespace ERUNTIME_NAMESPACE
{
    /*
     Command Args
     */
    
    CommandArgs::CommandArgs(const std::vector<StringView>& args)
        : m_Args(args)
    {
    }

    CommandArgs CommandArgs::Parse(StringView str)
    {
        std::vector<StringView> args;

        size_t start, end;

        start = end = 0;

        while((start = str.find_first_not_of(' ', end)) != std::string::npos)
        {
            end = str.find(' ', start);
            args.push_back(str.substr(start, end - start));
        }

        return CommandArgs(args);
    }

    std::size_t CommandArgs::Count() const
    {
        return m_Args.size();
    }

    /*
     String Command Runner
     */

    StringCommandRunner& StringCommandRunner::Instance()
    {
        static StringCommandRunner s_Runner;
        return s_Runner;
    }

    std::expected<void, String> StringCommandRunner::Run(StringView cmd)
    {
        auto firstNonSpace = String::npos;

        for(size_t i = 0; i < cmd.size(); i++)
        {
            if(std::isspace(cmd[i]) == 0)
            {
            firstNonSpace = i;
                break;
            }
        }

        if (firstNonSpace == String::npos)
            return std::unexpected("Failed to run command: Can't find token start (maybe it's empty?)");

        auto firstTokenEnd = firstNonSpace;
        for (size_t i = firstNonSpace; i < cmd.size(); i++)
        {
          if (std::isspace(cmd[i]))
            break;

          firstTokenEnd++;
        }

        if (firstTokenEnd == String::npos)
            return std::unexpected("Failed to run command: Can't find token end");

        String cmdSearchStr = String(
            cmd.substr(firstNonSpace, firstTokenEnd - firstNonSpace));

        std::lock_guard<std::mutex> lock(m_Sync);
        auto searchIt = m_CommandMap.find(cmdSearchStr);
        if (searchIt == m_CommandMap.end())
        {
          return std::unexpected(std::format(
              "Failed to run unexisting command: {}", cmdSearchStr));
        }

        auto args = String(cmd.substr(
            firstTokenEnd, cmd.size() - firstTokenEnd));

        (searchIt->second)(CommandArgs::Parse(args));

        return {};
    }

    std::expected<void, String> StringCommandRunner::AddCommand(CommandSpecification cmd, CommandCallback callback)
    {
        std::lock_guard<std::mutex> lock(m_Sync);

        if (m_CommandMap.contains(cmd.Name))
        {
            return std::unexpected(std::format("Failed to add command. Command already exists: {}", cmd.Name));
        }

        m_CommandSpecMap.insert({cmd.Name, cmd});
        m_CommandMap.insert({m_CommandSpecMap.at(cmd.Name).Name, callback});

        return {};
    }

    std::expected<void, String> StringCommandRunner::RemoveCommand(StringView cmd)
    {
        std::lock_guard<std::mutex> lock(m_Sync);

        if(!m_CommandMap.contains(cmd))
        {
            return std::unexpected(std::format("Failed to remove command. Command doesn't exists: {}", cmd));
        }

        m_CommandMap.erase(cmd);
        m_CommandSpecMap.erase(cmd);

        return {};
    }

    std::expected<CommandSpecification, String> StringCommandRunner::GetSpec(StringView cmd) const
    {
        if(!m_CommandSpecMap.contains(cmd))
        {
            return std::unexpected(std::format("Failed to get command specification. Command doesn't exists: {}", cmd));
        }

        return m_CommandSpecMap.at(cmd);
    }

    void StringCommandRunner::Each(std::function<void(const CommandSpecification& spec)> callback) const
    {
      for (auto &specIt : m_CommandSpecMap)
        {
            (callback)(specIt.second);
        }
    }
}