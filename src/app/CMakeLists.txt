project("App")


add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
        PRIVATE
        ElementCreationService.hh
        ElementCreationService.cc
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../../include/app/IElementCreationRegistry.hh
        ${CMAKE_CURRENT_SOURCE_DIR}/../../include/app/IElementCreationService.hh
)

include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME}
        BASE_NAME APP
        EXPORT_MACRO_NAME APP_API
        EXPORT_FILE_NAME "${CMAKE_CURRENT_BINARY_DIR}/include/app/exports.h"
        DEPRECATED_MACRO_NAME MYLIB_APP_DEPRECATED
)

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ..
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/>
        $<INSTALL_INTERFACE:include>
)


target_link_libraries(${PROJECT_NAME}
        PRIVATE
        CMakeCwAPI3D::Math
)

install(
        FILES ${CMAKE_CURRENT_BINARY_DIR}/include/app/exports.h
        DESTINATION include/app
)


add_library(CMakeCwAPI3D::App ALIAS App)

