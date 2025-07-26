// CMakeCwAPI3D.cpp : Defines the entry point for the application.
//
#include <cwapi3d/CwAPI3D.h>
#include "CMakeCwAPI3D.h"

#include "ElementFromPointsFactory.h"

CWAPI3D_PLUGIN bool plugin_x64_init(CwAPI3D::ControllerFactory *factory)
{
    if (factory == nullptr) {
        return false;
    }

    app::element::factory::ElementFromPointsFactory::registerElementType(
        app::element::factory::ElementFromPointsFactory::Beam,
        [elementController = factory->getElementController()](const double width,
                                                              const double height,
                                                              const CwAPI3D::vector3D &p1,
                                                              const CwAPI3D::vector3D &p2,
                                                              const CwAPI3D::vector3D &p3)
        {
            return elementController->createRectangularBeamPoints(width, height, p1, p2, p3);
        });

    const auto elementDimension = app::element::ElementDimension(4500.0, 120.0, 240.0);

    const app::math::Vector3D xDirection(1.0, 0.0, 0.0);
    const app::math::Vector3D yDirection(0.0, 1.0, 0.0);
    const app::math::Vector3D zDirection(0.0, 0.0, 1.0);
    constexpr app::math::Point3D origin(10.0, 5.0, 0.0);

    const app::element::ElementLocalAxis axisSystem(xDirection, yDirection, zDirection, origin);
    const auto beamId = app::element::factory::ElementFromPointsFactory::createElementFromPoints(
        app::element::factory::ElementFromPointsFactory::Beam,
        elementDimension,
        axisSystem
    );


    // auto elementLocalAxis = app::element::ElementLocalAxis<app::math::Point3D>();
    // elementLocalAxis.setLengthAxisStartPt(0.0, 0.0, 0.0);
    // const auto endPt = elementLocalAxis.getLengthAxisStartPt() * app::math::Vector3D(4500.0, 0.0, 0.0);
    // elementLocalAxis.setLengthAxisEndPt(endPt.x, endPt.y, endPt.z);
    // const auto heightPt = elementLocalAxis.getLengthAxisEndPt() * app::math::Vector3D(0.0, 1.0, 0.0);
    // elementLocalAxis.setHeightPt(heightPt.x, heightPt.y, heightPt.z);
    //
    // const auto result = app::element::factory::ElementFromPointsFactory::createElementFromPoints<app::math::Point3D>(
    //     app::element::factory::ElementFromPointsFactory::Beam,
    //     elementDimension,
    //     elementLocalAxis);

    std::cout << "Created element ID: " << (beamId.has_value() ? std::to_string(beamId.value()) : "None") << std::endl;

    return true;
}
