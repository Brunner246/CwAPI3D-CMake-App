//
// Created by MichaelBrunner on 27/07/2025.
//

#pragma once

#include <app/exports.h>
#include <memory>
#include <optional>

#include "IElementCreationRegistry.hh"

namespace app::element::service
{
class IElementCreationService
{
public:
    virtual ~IElementCreationService() = default;

    [[nodiscard]] virtual std::optional<ElementID> createElementFromPoints(factory::IElementCreationRegistry::Type type,
                                                             const ElementDimension &dimensions,
                                                             const ElementLocalAxis &coordinateSystem) const = 0;

    virtual bool registerElementType(factory::IElementCreationRegistry::Type type,
                                     const std::function<std::optional<ElementID>(
                                         const ElementDimension &,
                                         const ElementLocalAxis &)> &creatorFunction) const = 0;
};

APP_API std::unique_ptr<IElementCreationService> createElementCreationService(
    std::unique_ptr<factory::IElementCreationRegistry> registry);
};
