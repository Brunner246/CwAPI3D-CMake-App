//
// Created by MichaelBrunner on 27/07/2025.
//

#include "app/CommandProcessor.hh"

#include <format>


namespace app::element::service
{
std::string CommandProcessor::processCommand(const std::string &command)
{
    return std::format("Executed: {}", command);
    // return QString("Executed: %1").arg(command);
}
//TODO: Use QSortFilterProxyModel for more advanced auto-completion.
std::vector<std::string> CommandProcessor::suggestCommands() const
{
    return m_commandList;
}
}
