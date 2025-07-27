//
// Created by MichaelBrunner on 27/07/2025.
//

#include "ElementCreationService.hh"

#include <iostream>
#include <stdexcept>

#include "models/ElementCreationException.hh"

namespace app::element::service
{
std::unique_ptr<IElementCreationService> createElementCreationService(
    std::unique_ptr<factory::IElementCreationRegistry> registry)
{
    return std::make_unique<ElementCreationService>(std::move(registry));
}

ElementCreationService::ElementCreationService(std::unique_ptr<factory::IElementCreationRegistry> registry)
    : elementCreationRegistry(std::move(registry))
{
    if (!elementCreationRegistry) {
        throw std::runtime_error("ElementCreationService: Registry cannot be null.");
    }
}

std::optional<ElementID> ElementCreationService::createElementFromPoints(factory::IElementCreationRegistry::Type type,
                                                                         const ElementDimension &dimensions,
                                                                         const ElementLocalAxis &coordinateSystem) const
{
    try {
        return elementCreationRegistry->create(type, dimensions, coordinateSystem);
    }
    catch (const ElementCreationException &e) {
        std::cout << "ElementCreationException: " << e.what() << std::endl;
        return std::nullopt;
    }
    catch (const std::runtime_error &e) {
        // rethrow
        //throw std::runtime_error(std::string("ElementCreationService: ") + e.what());
        std::cout << e.what() << std::endl;
        return std::nullopt;
    }
}

bool ElementCreationService::registerElementType(factory::IElementCreationRegistry::Type type,
                                                 const std::function<std::optional<ElementID>(
                                                     const ElementDimension &,
                                                     const ElementLocalAxis &)> &creatorFunction) const
{
    return elementCreationRegistry->registerElementType(type, creatorFunction);
}
}
