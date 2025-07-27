//
// Created by MichaelBrunner on 27/07/2025.
//

#pragma once
#include <stdexcept>

class ApplicationException: public std::runtime_error
{
public:
    explicit ApplicationException(const std::string &message)
        : std::runtime_error(message)
    {
    }

    explicit ApplicationException(const char *message)
        : std::runtime_error(message)
    {
    }
};
