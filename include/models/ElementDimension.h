#pragma once
#include "math/Vector3D.h"

namespace app::element
{

  class ElementDimension
  {
    double length;
    double width;
    double height;

  public:
    explicit ElementDimension() : length(0.0), width(0.0), height(0.0) {}

    explicit ElementDimension(const double length, const double width, const double height)
      : length(length), width(width), height(height) {
    }

    void setLength(const double length) {
      this->length = length;
    }
    void setWidth(const double width) {
      this->width = width;
    }
    void setHeight(const double height) {
      this->height = height;
    }

    [[nodiscard]] double getLength() const {
      return length;
    }

    [[nodiscard]] double getWidth() const {
      return width;
    }

    [[nodiscard]] double getHeight() const {
      return height;
    }

  };
} // namespace app::element
