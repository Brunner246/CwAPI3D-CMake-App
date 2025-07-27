//
// Created by MichaelBrunner on 27/07/2025.
//

#pragma once
#include <functional>
#include <optional>

using ElementID = std::uint64_t;

namespace app::element
{
class ElementLocalAxis;
class ElementDimension;
}

using ElementID = std::uint64_t;

namespace app::element::factory
{
class IElementCreationRegistry
{
public:
    enum Type { Beam, Panel };

    virtual ~IElementCreationRegistry() = default;

    virtual std::optional<ElementID> create(Type type,
                                            const ElementDimension &dimensions,
                                            const ElementLocalAxis &coordinateSystem) = 0;

    virtual bool registerElementType(Type type,
                                     const std::function<std::optional<ElementID>(
                                         const ElementDimension &,
                                         const ElementLocalAxis &)> &creatorFunction) = 0;
};
}
