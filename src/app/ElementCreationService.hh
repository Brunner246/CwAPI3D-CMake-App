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
    std::unique_ptr<factory::IElementCreationRegistry> elementCreationRegistry;

public:
    explicit ElementCreationService(std::unique_ptr<factory::IElementCreationRegistry> registry);

    [[nodiscard]] std::optional<ElementID> createElementFromPoints(factory::IElementCreationRegistry::Type type,
                                                     const ElementDimension &dimensions,
                                                     const ElementLocalAxis &coordinateSystem) const override;

    bool registerElementType(factory::IElementCreationRegistry::Type type,
                             const std::function<std::optional<ElementID>(
                                 const ElementDimension &,
                                 const ElementLocalAxis &)> &creatorFunction) const override;
};
}
