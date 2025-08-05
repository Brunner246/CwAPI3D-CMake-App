//
// Created by MichaelBrunner on 27/07/2025.
//

#pragma once
#include <string>
#include <vector>

class ICommandProcessor
{
public:
    virtual ~ICommandProcessor() = default;

    virtual std::string processCommand(const std::string &command) = 0;

    [[nodiscard]] virtual std::vector<std::string> suggestCommands() const = 0;
};
