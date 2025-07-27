project("CwAdapter")

message(STATUS "Binary directory: ${CMAKE_CURRENT_BINARY_DIR}")

add_library(${PROJECT_NAME})

FetchContent_GetProperties(cwapi3dcpp SOURCE_DIR cwapi3dcpp_source_dir)

target_sources(${PROJECT_NAME}
        PRIVATE
        #Vector3D.cpp
        ElementCreationRegistry.cpp
        library.cc
        PUBLIC
        #${CMAKE_CURRENT_SOURCE_DIR}/../../include/math/Vector3D.h
        ElementCreationRegistry.h
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
        CWAPI3D_PLUGIN_NAME=L"Cadwork Test Plugin"
        CWAPI3D_AUTHOR_NAME=L"Your Name"
        CWAPI3D_AUTHOR_EMAIL=L"your_name@something.swiss"
)


include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME}
        BASE_NAME ADAPTER
        EXPORT_MACRO_NAME ADAPTER_API
        EXPORT_FILE_NAME "${CMAKE_CURRENT_BINARY_DIR}/include/cwAdapter/exports.h"
        DEPRECATED_MACRO_NAME MYLIB_CORE_DEPRECATED
)

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${cwapi3dcpp_source_dir}/include
        # ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/app/>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/math/>
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/cwAdapter/>
        $<INSTALL_INTERFACE:include>
)

install(
        FILES ${CMAKE_CURRENT_BINARY_DIR}/include/cwAdapter/exports.h
        DESTINATION include/cwAdapter
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        CMakeCwAPI3D::Math
        CMakeCwAPI3D::App
)


add_library(CMakeCwAPI3D::CwAdapter ALIAS CwAdapter)