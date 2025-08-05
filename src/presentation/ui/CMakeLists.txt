project(CmdUi)

# check why it is only working like this and not from preset
#set(CMAKE_PREFIX_PATH "C:/source/cadlib/3rdParty/v_32.0/Qt/x64/lib/cmake/Qt5/")
message(STATUS "CMake prefix path: ${CMAKE_PREFIX_PATH}")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

include(GenerateExportHeader)
include(GNUInstallDirs)

find_package(Qt5
        COMPONENTS
        Core
        Widgets
        QuickWidgets
        REQUIRED)

#qt5_add_resources(UI_RESOURCES resources.qrc)
#qt_add_resources(${PROJECT_NAME}
#        PREFIX "/qml"
#        FILES
#        CommandDock.qml
#
##        PREFIX "/public"
##        FILES
##        public/add.svg
#
#)

add_library(${PROJECT_NAME})

#target_compile_definitions(${PROJECT_NAME} PRIVATE UI_EXPORTS)

generate_export_header(${PROJECT_NAME}
        BASE_NAME UI
        EXPORT_MACRO_NAME UI_API
        EXPORT_FILE_NAME "${CMAKE_CURRENT_BINARY_DIR}/include/ui/exports.h"
        STATIC_DEFINE ${PROJECT_NAME}_BUILT_AS_STATIC
)

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ..
        ${CMAKE_CURRENT_SOURCE_DIR}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/>
        $<INSTALL_INTERFACE:include>
)

qt5_add_resources(UI_RESOURCES resources.qrc)
target_sources(${PROJECT_NAME} PRIVATE ${UI_RESOURCES})

#add_library(ui SHARED
#        ${UI_SOURCES}
#        ${UI_HEADERS}
#)

target_sources(${PROJECT_NAME}
        PRIVATE
        commanddialog.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../include/presentation/ui/commanddialog.hh
        commanddialog.ui
        resources.qrc

        #        PUBLIC
        #        FILE_SET HEADERS BASE_DIRS include
        #        FILES

)

install(
        FILES ${CMAKE_CURRENT_BINARY_DIR}/include/ui/exports.h
        DESTINATION include/ui
)


add_library(CMakeCwAPI3D::Ui ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        Qt5::Core
        Qt5::Widgets
        Qt5::QuickWidgets

        CMakeCwAPI3D::ViewModel
)