#include "../../include/math/Vector3D.h"

#include <stdexcept>

//TODO: Find another solution, i do not want depend on CwAPI3D in this project
// #include "cwapi3d/CwAPI3DTypes.h"

app::math::Point3D app::math::Point3D::operator+(const Vector3D &vec) const
{
  return Point3D(x + vec.x, y + vec.y, z + vec.z);
}
app::math::Vector3D app::math::Point3D::operator-(const Point3D &other) const
{
  return Vector3D(x - other.x, y - other.y, z - other.z);
}
app::math::Vector3D app::math::Vector3D::operator+(const Vector3D& other) const
{
  return Vector3D(x + other.x, y + other.y, z + other.z);
}

app::math::Vector3D app::math::Vector3D::operator-(const Vector3D& other) const
{
  return Vector3D(x - other.x, y - other.y, z - other.z);
}

//app::math::Vector3D app::math::Vector3D::operator*(double scalar) const
//{
//  return Vector3D(x * scalar, y * scalar, z * scalar);
//}

double app::math::Vector3D::dot(const Vector3D& other) const
{
  return x * other.x + y * other.y + z * other.z;
}

app::math::Vector3D app::math::Vector3D::cross(const Vector3D& other) const
{
  return Vector3D(
    y * other.z - z * other.y,
    z * other.x - x * other.z,
    x * other.y - y * other.x
  );
}

double app::math::Vector3D::magnitude() const
{
  return std::sqrt(x * x + y * y + z * z);
}

app::math::Vector3D app::math::Vector3D::normalize() const
{
  const double mag = magnitude();
  if (std::isfinite(mag) && mag < 1e-10) {
    return Vector3D(0, 0, 0);
  }
  return Vector3D(x / mag, y / mag, z / mag);
}

app::math::Vector3D app::math::Vector3D::operator-() const
{
  return Vector3D(-x, -y, -z);
}

bool app::math::Vector3D::operator==(const Vector3D& other) const
{
  if (std::fabs(x - other.x) < 1e-10 &&
    std::fabs(y - other.y) < 1e-10 &&
    std::fabs(z - other.z) < 1e-10) {
    return true;
  }
  return false;
}

// app::math::Vector3D::operator CwAPI3D::vector3D() const
// {
//   return CwAPI3D::vector3D(x, y, z);
// }

