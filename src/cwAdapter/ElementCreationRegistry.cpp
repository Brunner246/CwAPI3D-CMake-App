#include <cwapi3d/CwAPI3D.h>
#include "ElementCreationRegistry.h"
#include "math/Vector3D.h"
#include "models/ElementCreationException.hh"

auto app::element::utils::toCwVector(const math::Vector3D &vec) -> CwAPI3D::vector3D
{
    return CwAPI3D::vector3D(vec.x, vec.y, vec.z);
}
auto app::element::utils::toCwVector(const math::Point3D &point) -> CwAPI3D::vector3D
{
    return CwAPI3D::vector3D(point.x, point.y, point.z);
}

std::optional<ElementID> app::element::factory::ElementCreationRegistry::create(const Type type,
    const ElementDimension &dimensions,
    const ElementLocalAxis &coordinateSystem)
{
    if (registry.empty()) {
        throw ElementCreationException(ElementCreationException::ErrorCode::ELEMENT_NOT_REGISTERED,
                                       "ElementCreationService: Registry cannot be null.");

    }
    const auto it = registry.find(type);
    if (it == registry.end()) {
        throw ElementCreationException(ElementCreationException::ErrorCode::ELEMENT_NOT_REGISTERED,
                                        "Element type not registered in ElementCreationRegistry.");
    }
    const auto &creatorFunction = it->second;
    const auto startPoint = coordinateSystem.getOrigin();
    const auto xAxisVector = coordinateSystem.getXAxis();
    auto endPoint = startPoint + (xAxisVector * dimensions.getLength());
    auto heightPoint = coordinateSystem.getHeightPoint();
    return creatorFunction(dimensions, coordinateSystem);
}

bool app::element::factory::ElementCreationRegistry::registerElementType(const Type type,
                                                                         const std::function<std::optional<ElementID>(
                                                                             const ElementDimension &,
                                                                             const ElementLocalAxis &)> &
                                                                         creatorFunction)
{
    if (registry.contains(type)) {
        return false;
    }
    registry[type] = creatorFunction;
    return true;
}
