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
inline auto toCwVector(const math::Vector3D &vec) -> CwAPI3D::vector3D;

inline auto toCwVector(const math::Point3D &point) -> CwAPI3D::vector3D;
}

namespace app::element::factory
{
class ElementFromPointsFactory
{
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

        return creatorFunction(
            dimensions.getWidth(),
            dimensions.getHeight(),
            utils::toCwVector(startPoint),
            utils::toCwVector(endPoint),
            utils::toCwVector(heightPoint)
        );
    }

    static bool registerElementType(Type type,
                                    const std::function<std::optional<ElementID>(
                                        double,
                                        double,
                                        CwAPI3D::vector3D,
                                        CwAPI3D::vector3D,
                                        CwAPI3D::vector3D)> &creatorFunction);

private:
    using Registry = std::unordered_map<Type, std::function<std::optional<ElementID>(
                                            double,
                                            double,
                                            CwAPI3D::vector3D,
                                            CwAPI3D::vector3D,
                                            CwAPI3D::vector3D)> >;
    static inline Registry registry;
};
}
