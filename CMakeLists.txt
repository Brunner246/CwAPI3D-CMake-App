
cmake_minimum_required (VERSION 3.31)

# Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("CMakeCwAPI3D")
set(CMAKE_CXX_STANDARD 20)


option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(BUILD_TESTS "Build test programs" ON)

include(FetchContent)
FetchContent_Declare(
        cwapi3dcpp
        GIT_REPOSITORY https://github.com/cwapi3d/cwapi3dcpp.git
        GIT_TAG main
)

FetchContent_MakeAvailable(cwapi3dcpp) 

add_subdirectory(src/math)
add_subdirectory(include/models)
add_subdirectory(src/app)
add_subdirectory(src/cwAdapter)


# set_property(TARGET CMakeCwAPI3D PROPERTY CXX_STANDARD 20)


# TODO: Add tests and install targets if needed.
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
