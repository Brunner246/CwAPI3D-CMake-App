#pragma once
#include <cstdint>
#include <functional>
#include <optional>
#include <stdexcept>
#include <unordered_map>

#include "ElementDimension.h"
#include "ElementLocalAxis.h"

namespace app::math
{
class Vector3D;
}

namespace CwAPI3D
{
struct vector3D;
}

namespace CwAPI3D::Interfaces
{
class ICwAPI3DElementController;
}

using ElementID = std::uint64_t;

namespace app::element::utils
{
auto toCwVector(const math::Vector3D &vec) -> CwAPI3D::vector3D;

auto toCwVector(const math::Point3D &point) -> CwAPI3D::vector3D;
}

namespace app::element::factory
{
class ElementCreationRegistry
{
    using ElementCreatorFunction = std::function<std::optional<ElementID>(
        const ElementDimension &,
        const ElementLocalAxis &)>;

public:
    enum Type { Beam, Panel };

    template<CoordinateSystem CoordSys> static std::optional<ElementID> createElementFromPoints(const Type type,
        const ElementDimension &dimensions,
        const CoordSys &coordinateSystem)
    {
        if (registry.empty()) {
            throw std::runtime_error("No element types registered in ElementFromPointsFactory.");
        }

        const auto it = registry.find(type);
        if (it == registry.end()) {
            throw std::runtime_error("Element type not registered in ElementFromPointsFactory.");
        }

        const auto &creatorFunction = it->second;

        auto startPoint = coordinateSystem.getOrigin();
        auto xAxisVector = coordinateSystem.getXAxis();
        auto endPoint = startPoint + (xAxisVector * dimensions.getLength());
        auto heightPoint = coordinateSystem.getHeightPoint();

        return creatorFunction(dimensions, coordinateSystem);
    }

    static bool registerElementType(Type type, const ElementCreatorFunction &creatorFunction);

private:
    using Registry = std::unordered_map<Type, ElementCreatorFunction>;
    static inline Registry registry;
};
}
