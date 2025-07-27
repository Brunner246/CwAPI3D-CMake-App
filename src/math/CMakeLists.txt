project("Math")

message(STATUS "Binary directory: ${CMAKE_CURRENT_BINARY_DIR}")

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
        PRIVATE
        Vector3D.cpp
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../../include/math/Vector3D.h
)

include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME}
        BASE_NAME MATH
        EXPORT_MACRO_NAME MATH_API
        EXPORT_FILE_NAME "${CMAKE_CURRENT_BINARY_DIR}/include/math/exports.h"
        DEPRECATED_MACRO_NAME MYLIB_CORE_DEPRECATED
)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        # ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}
)

install(
        FILES ${CMAKE_CURRENT_BINARY_DIR}/include/math/exports.h
        DESTINATION include/math
)


add_library(CMakeCwAPI3D::Math ALIAS Math)