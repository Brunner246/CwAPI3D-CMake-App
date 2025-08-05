//
// Created by MichaelBrunner on 27/07/2025.
//

#pragma once
#include <memory>
#include <app/exports.h>
#include "app/IElementCreationRegistry.hh"
#include "app/IElementCreationService.hh"

namespace app::element::service
{
class APP_API ElementCreationService final: public IElementCreationService
{
    std::unique_ptr<registry::IElementCreationRegistry> elementCreationRegistry;

public:
    explicit ElementCreationService(std::unique_ptr<registry::IElementCreationRegistry> registry);

    [[nodiscard]] std::optional<ElementID> createElementFromPoints(registry::IElementCreationRegistry::Type type,
                                                     const ElementDimension &dimensions,
                                                     const ElementLocalAxis &coordinateSystem) const override;

    bool registerElementType(registry::IElementCreationRegistry::Type type,
                             const std::function<std::optional<ElementID>(
                                 const ElementDimension &,
                                 const ElementLocalAxis &)> &creatorFunction) const override;
};
}
