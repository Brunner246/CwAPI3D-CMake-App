project("Test")
# https://google.github.io/googletest/quickstart-cmake.html

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME} 
example.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
        ${CMAKE_CURRENT_SOURCE_DIR}/../src
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/app/>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/math/>
)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        gtest_main
        gmock
        CMakeCwAPI3D::Math
)

add_test(NAME ApiTests COMMAND ${PROJECT_NAME})


