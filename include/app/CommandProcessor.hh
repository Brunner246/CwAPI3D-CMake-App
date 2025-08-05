//
// Created by MichaelBrunner on 27/07/2025.
//

#pragma once

#include <app/exports.h>
#include <string>
#include <vector>

#include "models/presentation/ICommandProcessor.hh"

namespace app::element::service
{

class APP_API CommandProcessor : public ICommandProcessor {
public:
    std::string processCommand(const std::string& command) override;

    [[nodiscard]] std::vector<std::string> suggestCommands() const override;

private:
    std::vector<std::string> m_commandList {
        "create_beam_rectangular_points",
        "create_beam_circular",
        "delete_element",
        "export_to_csv"
    };
};

}
