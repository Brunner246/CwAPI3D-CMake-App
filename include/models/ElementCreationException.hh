//
// Created by MichaelBrunner on 27/07/2025.
//

#include "ApplicationException.hh"

class ElementCreationException final: public ApplicationException {
public:
    enum class ErrorCode {
        CREATION_FAILED,
        INVALID_DIMENSIONS,
        INVALID_COORDINATE_SYSTEM,
        ELEMENT_NOT_REGISTERED
    };

private:
    ErrorCode errorCode;

public:
    ElementCreationException(const ErrorCode code, const std::string& message)
        : ApplicationException("Element creation error: " + message),
          errorCode(code) {}

    [[nodiscard]] ErrorCode getErrorCode() const noexcept {
        return errorCode;
    }
};
