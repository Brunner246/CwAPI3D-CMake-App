#include "math/Vector3D.h"

#include <cmath>
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
uint32_t app::math::add(uint32_t a, uint32_t b)
{
    return a + b;
}
app::math::Vector3D app::math::Vector3D::operator+(const Vector3D &other) const
{
    return Vector3D(x + other.x, y + other.y, z + other.z);
}

app::math::Vector3D app::math::Vector3D::operator-(const Vector3D &other) const
{
    return Vector3D(x - other.x, y - other.y, z - other.z);
}

//app::math::Vector3D app::math::Vector3D::operator*(double scalar) const
//{
//  return Vector3D(x * scalar, y * scalar, z * scalar);
//}

double app::math::Vector3D::dot(const Vector3D &other) const
{
    return x * other.x + y * other.y + z * other.z;
}

app::math::Vector3D app::math::Vector3D::cross(const Vector3D &other) const
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

bool app::math::Vector3D::operator==(const Vector3D &other) const
{
    if (std::fabs(x - other.x) < 1e-10 &&
        std::fabs(y - other.y) < 1e-10 &&
        std::fabs(z - other.z) < 1e-10) {
        return true;
    }
    return false;
}
bool app::math::Vector3D::operator!=(const Vector3D &other) const
{
    return !(*this == other);
}
double app::math::Vector3D::operator[](const int index) const
{
    switch (index) {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    default: throw std::out_of_range("Index out of range for Vector3D");
    }
}

void app::math::Vector3D::set(const int index, const double value)
{
    switch (index) {
    case 0: this->x = value;
        break;
    case 1: this->y = value;
        break;
    case 2: this->z = value;
        break;
    default: throw std::out_of_range("Index out of range for Vector3D");
    }
}

// app::math::Vector3D::operator CwAPI3D::vector3D() const
// {
//   return CwAPI3D::vector3D(x, y, z);
// }
