#pragma once
#include <cmath>
#include <exports.h>

namespace CwAPI3D
{
  struct vector3D;
}

namespace app::math
{
class Vector3D;
//TODO: Define in separate header file
  struct MATH_API Point3D {
    double x, y, z;

    Point3D operator+(const Vector3D& vec) const;

    Vector3D operator-(const Point3D& other) const;

  };


//TODO
  class MATH_API Vector3D
  {
  public:
    double x, y, z;

    explicit Vector3D(const double x = 0.0, const double y = 0.0, const double z = 0.0) : x(x), y(y), z(z) {}

    Vector3D operator+(const Vector3D& other) const;

    Vector3D operator-(const Vector3D& other) const;

    //Vector3D operator*(double scalar) const;

    [[nodiscard]] double dot(const Vector3D& other) const;

    [[nodiscard]] Vector3D cross(const Vector3D& other) const;

    [[nodiscard]] double magnitude() const;

    [[nodiscard]] Vector3D normalize() const;

    Vector3D operator-() const;

    bool operator==(const Vector3D& other) const;

   // explicit operator CwAPI3D::vector3D() const;

  };

  //inline Vector3D operator+(const Vector3D& lhs, const Vector3D& rhs) {
  //  return Vector3D(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
  //}

  inline Vector3D operator-(const Vector3D& lhs, const Vector3D& rhs) {
    return Vector3D(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
  }

  inline Vector3D operator*(const Vector3D& vec, double scalar) {
    return Vector3D(vec.x * scalar, vec.y * scalar, vec.z * scalar);
  }

  inline Vector3D operator*(double scalar, const Vector3D& vec) {
    return Vector3D(vec.x * scalar, vec.y * scalar, vec.z * scalar);
  }

  inline Point3D operator*(const Point3D& point, const Vector3D& vec) {
    return Point3D{ point.x * vec.x, point.y * vec.y, point.z * vec.z };
  }

  inline Point3D operator*(const Vector3D& vec, const Point3D& point) {
    return Point3D{ point.x * vec.x, point.y * vec.y, point.z * vec.z };
  }

}
