#pragma once

#include <cmath>
#include <concepts>

#include "math/Vector3D.h"

template <typename T>
concept VectorOrPointType =
  requires(T t) {
  // { std::array{ t[0], t[1], t[2] } }; //  indexable with 3 elements
    requires std::same_as<std::remove_cvref_t<decltype(t)>, app::math::Vector3D> ||
std::same_as<std::remove_cvref_t<decltype(t)>, app::math::Point3D>;
};

template<typename T>
concept CoordinateSystem = requires(T t) {

  { t.getOrigin() } -> std::convertible_to<app::math::Point3D>;
  // { t.getLengthAxisEndPoint() } -> std::convertible_to<app::math::Point3D>;
  { t.getHeightPoint() } -> std::convertible_to<app::math::Point3D>;

  { t.getXAxis() } -> std::convertible_to<app::math::Vector3D>;
  { t.getYAxis() } -> std::convertible_to<app::math::Vector3D>;
  { t.getZAxis() } -> std::convertible_to<app::math::Vector3D>;
};



namespace app::element
{
class ElementLocalAxis {
private:
    math::Vector3D xAxis;
    math::Vector3D yAxis;
    math::Vector3D zAxis;
    math::Point3D origin{0.0, 0.0, 0.0};

public:
    explicit ElementLocalAxis()
        : xAxis(1.0, 0.0, 0.0), yAxis(0.0, 1.0, 0.0), zAxis(0.0, 0.0, 1.0) {}

    explicit ElementLocalAxis(const math::Vector3D& xAxis,
                             const math::Vector3D& yAxis,
                             const math::Vector3D& zAxis,
                             const math::Point3D& origin = {0.0, 0.0, 0.0})
        : xAxis(xAxis), yAxis(yAxis), zAxis(zAxis), origin(origin) {}

    [[nodiscard]] math::Vector3D getXAxis() const { return xAxis; }
    [[nodiscard]] math::Vector3D getYAxis() const { return yAxis; }
    [[nodiscard]] math::Vector3D getZAxis() const { return zAxis; }

    [[nodiscard]] math::Point3D getOrigin() const { return origin; }
    // [[nodiscard]] math::Point3D getLengthAxisEndPoint() const {
    //     return origin; // + xAxis; // Point + Vector = Point
    // }
    [[nodiscard]] math::Point3D getHeightPoint() const {
        return origin + zAxis; // Point + Vector = Point
    }


    void setXAxis(const math::Vector3D& axis) { this->xAxis = axis; }
    void setYAxis(const math::Vector3D& axis) { this->yAxis = axis; }
    void setZAxis(const math::Vector3D& axis) { this->zAxis = axis; }
    void setOrigin(const math::Point3D& orig) { this->origin = orig; }
};

template<VectorOrPointType T>
class ElementLocalCoordinateSystemAdapter {

    ElementLocalAxis coordSystem;

public:
    explicit ElementLocalCoordinateSystemAdapter(const ElementLocalAxis& cs)
        : coordSystem(cs) {}

    [[nodiscard]] math::Vector3D getXAxis() const {
        const auto start = coordSystem.getOrigin();
        const auto end = coordSystem.getLengthAxisEndPoint();
        return math::Vector3D(end.x - start.x, end.y - start.y, end.z - start.z).normalize();
    }

    [[nodiscard]] math::Vector3D getYAxis() const {
        const auto xAxis = getXAxis();
        const auto zAxis = getZAxis();
        return zAxis.cross(xAxis).normalize();
    }

    [[nodiscard]] math::Vector3D getZAxis() const {
        const auto start = coordSystem.getOrigin();
        const auto height = coordSystem.getHeightPoint();
        const auto heightVector = math::Vector3D(height.x - start.x, height.y - start.y, height.z - start.z);
        const auto xAxis = getXAxis();
        return xAxis.cross(heightVector).normalize();
    }

    [[nodiscard]] math::Point3D getOrigin() const {
        const auto origin = coordSystem.getOrigin();
        return math::Point3D(origin.x, origin.y, origin.z);
    }

    [[nodiscard]] math::Point3D getLengthAxisEndPoint() const {
        const auto end = coordSystem.getLengthAxisEndPoint();
        return math::Point3D(end.x, end.y, end.z);
    }

    [[nodiscard]] math::Point3D getHeightPoint() const {
        const auto height = coordSystem.getHeightPoint();
        return math::Point3D(height.x, height.y, height.z);
    }
};

}
