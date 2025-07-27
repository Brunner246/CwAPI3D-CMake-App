//
// Created by MichaelBrunner on 27/07/2025.
//

#include <iostream>
#include <memory>
#include <cwapi3d/CwAPI3D.h>

#include "ElementCreationRegistry.h"
#include "app/IElementCreationService.hh"

CWAPI3D_PLUGIN bool plugin_x64_init(CwAPI3D::ControllerFactory *factory)
{
    if (factory == nullptr) {
        return false;
    }
    const auto elementCreationService = app::element::service::createElementCreationService(
        std::make_unique<app::element::factory::ElementCreationRegistry>());

    elementCreationService->registerElementType(app::element::factory::ElementCreationRegistry::Beam,
                                                [elementController = factory->getElementController()](
                                                const app::element::ElementDimension &elementDimension,
                                                const app::element::ElementLocalAxis &elementLocalAxis) ->
                                                std::optional<ElementID>
                                                {
                                                    if (elementController == nullptr) {
                                                        return std::nullopt;
                                                    }
                                                    const auto width = elementDimension.getWidth();
                                                    const auto height = elementDimension.getHeight();
                                                    const auto p1 = app::element::utils::toCwVector(
                                                        elementLocalAxis.getOrigin());
                                                    const auto movedEndPt = elementLocalAxis.getOrigin() +
                                                        (elementLocalAxis.getXAxis() * elementDimension.getLength());
                                                    const auto p2 = app::element::utils::toCwVector(movedEndPt);
                                                    const auto p3 = app::element::utils::toCwVector(
                                                        elementLocalAxis.getHeightPoint());
                                                    return elementController->createRectangularBeamPoints(
                                                        width,
                                                        height,
                                                        p1,
                                                        p2,
                                                        p3);
                                                });

    elementCreationService->registerElementType(
    app::element::factory::ElementCreationRegistry::Panel,
    [elementController = factory->getElementController()](const app::element::ElementDimension &elementDimension,
                                                          const app::element::ElementLocalAxis &elementLocalAxis) ->
    std::optional<ElementID>
    {
        if (elementController == nullptr) {
            return std::nullopt;
        }

        const auto width = elementDimension.getWidth();
        const auto height = elementDimension.getHeight();
        const auto length = elementDimension.getLength();
        const auto origin = app::element::utils::toCwVector(elementLocalAxis.getOrigin());

        const auto localXDir = app::element::utils::toCwVector(elementLocalAxis.getXAxis());
        const auto localZDir = app::element::utils::toCwVector(elementLocalAxis.getZAxis());

        return elementController->createRectangularPanelVectors(width,
                                                                height,
                                                                length,
                                                                origin,
                                                                localXDir,
                                                                localZDir);
    });

    const auto elementDimension = app::element::ElementDimension(4500.0, 120.0, 240.0);
    const app::math::Vector3D xDirection(1.0, 0.0, 0.0);
    const app::math::Vector3D yDirection(0.0, 1.0, 0.0);
    const app::math::Vector3D zDirection(0.0, 0.0, 1.0);
    constexpr app::math::Point3D origin(10.0, 5.0, 0.0);
    const app::element::ElementLocalAxis axisSystem(xDirection, yDirection, zDirection, origin);
    const auto beamId = elementCreationService->createElementFromPoints(
        app::element::factory::ElementCreationRegistry::Beam,
        elementDimension,
        axisSystem);

    std::cout << "Created element ID: " << (beamId.has_value() ? std::to_string(beamId.value()) : "None") <<
        std::endl;

    auto bounded = [=](const app::math::Point3D &pt)
    {
        return app::element::ElementLocalAxis(xDirection, yDirection, zDirection, pt);
    };
    std::cout << "Created element ID: " << (beamId.has_value() ? std::to_string(beamId.value()) : "None") <<
        std::endl;
    const auto panelId = elementCreationService->createElementFromPoints(
        app::element::factory::ElementCreationRegistry::Panel,
        app::element::ElementDimension(2500.0, 1250.0, 15.0),
        bounded(app::math::Point3D(1000.0, 500.0, 0.0))
    );
    std::cout << "Created element ID: " << (panelId.has_value() ? std::to_string(panelId.value()) : "None") <<
        std::endl;

    return true;
}
