project(CwPlugin)

message(STATUS "CMake prefix path: ${CMAKE_PREFIX_PATH}")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)


find_package(Qt5
        COMPONENTS
        Core
        Widgets
        QuickWidgets
        REQUIRED) # https://github.com/Brunner246/TimberDataETIM/blob/main/source/etimView/CMakeLists.txt


add_library(${PROJECT_NAME})

FetchContent_GetProperties(cwapi3dcpp SOURCE_DIR cwapi3dcpp_source_dir)

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ..
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${cwapi3dcpp_source_dir}/include

        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/>
        $<INSTALL_INTERFACE:include>
)

target_sources(${PROJECT_NAME}
        PRIVATE
        library.cc
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
        CWAPI3D_PLUGIN_NAME=L"Cadwork Test Plugin"
        CWAPI3D_AUTHOR_NAME=L"Your Name"
        CWAPI3D_AUTHOR_EMAIL=L"your_name@something.swiss"
)


add_library(CMakeCwAPI3D::CwPlugin ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        Qt5::Core
        Qt5::Widgets
        Qt5::QuickWidgets
        CMakeCwAPI3D::Ui
        CMakeCwAPI3D::ViewModel
        CMakeCwAPI3D::Math
        CMakeCwAPI3D::App
)