project("App")


add_library(${PROJECT_NAME})

FetchContent_GetProperties(cwapi3dcpp SOURCE_DIR cwapi3dcpp_source_dir)

target_sources(${PROJECT_NAME} PRIVATE
        "CMakeCwAPI3D.cpp"
        "CMakeCwAPI3D.h"
        "ElementFromPointsFactory.h"
        "ElementFromPointsFactory.cpp"
        "ElementDimension.h"
        "ElementLocalAxis.h")

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ..
        ${cwapi3dcpp_source_dir}/include
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<INSTALL_INTERFACE:include>
)

# TODO: Add tests and install targets if needed.

target_compile_definitions(${PROJECT_NAME} PRIVATE
        CWAPI3D_PLUGIN_NAME=L"Cadwork Test Plugin"
        CWAPI3D_AUTHOR_NAME=L"Your Name"
        CWAPI3D_AUTHOR_EMAIL=L"your_name@something.swiss"
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        CMakeCwAPI3D::Math
)

add_library(CMakeCwAPI3D::App ALIAS App)

