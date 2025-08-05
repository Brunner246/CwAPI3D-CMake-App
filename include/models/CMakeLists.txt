project(Models)
add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME}

        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/models>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/models/presentation>
        $<INSTALL_INTERFACE:include>
)

