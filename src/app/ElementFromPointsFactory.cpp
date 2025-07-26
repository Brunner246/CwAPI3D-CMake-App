#include <cwapi3d/CwAPI3D.h>
#include "ElementFromPointsFactory.h"
#include "math/Vector3D.h"

#include <stdexcept>

//namespace app::element::utils
//{
//  auto toCwVector(const math::Vector3D& vec) -> CwAPI3D::vector3D
//  {
//    return CwAPI3D::vector3D(vec.x, vec.y, vec.z);
//  }
//}

//std::optional<ElementID> app::element::factory::ElementFromPointsFactory::createElementFromPoints(
//  const Type type,
//  const ElementDimension& aElementDimension,
//  const ElementLocalCoordinateSystem& aElementLocalAxis)
//{
//  if (registry.empty())
//  {
//    throw std::runtime_error("No element types registered in ElementFromPointsFactory.");
//  }
//  const auto it = registry.find(type);
//  if (it == registry.end())
//  {
//    throw std::runtime_error("Element type not registered in ElementFromPointsFactory.");
//  }
//  const auto& creatorFunction = it->second;
//  return creatorFunction(aElementDimension.getWidth(), aElementDimension.getHeight(),
//    utils::toCwVector(aElementLocalAxis.getXAxis()),
//    utils::toCwVector(aElementLocalAxis.getXAxis() * aElementDimension.getLength()),
//    aElementLocalAxis.getZAxis() + aElementLocalAxis.getXAxis()); // use implicit conversion to CwAPI3D::vector3D
//}

bool app::element::factory::ElementFromPointsFactory::registerElementType(Type type,
  const std::function<std::optional<ElementID>(
    double, double, CwAPI3D::vector3D,
    CwAPI3D::vector3D, CwAPI3D::vector3D)>
  & creatorFunction)
{
  if (registry.contains(type))
  {
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
