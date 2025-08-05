project(viewmodel)

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
        REQUIRED) # https://github.com/Brunner246/TimberDataETIM/blob/main/source/etimView/CMakeLists.txt

add_library(${PROJECT_NAME})

generate_export_header(${PROJECT_NAME}
        BASE_NAME VM
        EXPORT_MACRO_NAME VM_API
        EXPORT_FILE_NAME "${CMAKE_CURRENT_BINARY_DIR}/include/viewmodel/exports.h"
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

target_sources(${PROJECT_NAME}
        PRIVATE
        CommandViewModel.cc


        PUBLIC
#        FILE_SET HEADERS BASE_DIRS include
#        FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../include/presentation/viewmodel/CommandViewModel.hh
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../include/presentation/viewmodel/exports.h

)

install(
        FILES ${CMAKE_CURRENT_BINARY_DIR}/include/viewmodel/exports.h
        DESTINATION include/viewmodel
)


add_library(CMakeCwAPI3D::ViewModel ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        Qt5::Core
)