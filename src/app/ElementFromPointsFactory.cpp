#include <cwapi3d/CwAPI3D.h>
#include "ElementFromPointsFactory.h"
#include "math/Vector3D.h"


bool app::element::factory::ElementFromPointsFactory::registerElementType(const Type type,
                                                                          const ElementCreatorFunction &creatorFunction)
{
    if (registry.contains(type)) {
        return false;
    }
    registry[type] = creatorFunction;
    return true;
}
auto app::element::utils::toCwVector(const math::Vector3D &vec) -> CwAPI3D::vector3D
{
    return CwAPI3D::vector3D(vec.x, vec.y, vec.z);
}
auto app::element::utils::toCwVector(const math::Point3D &point) -> CwAPI3D::vector3D
{
    return CwAPI3D::vector3D(point.x, point.y, point.z);
}
