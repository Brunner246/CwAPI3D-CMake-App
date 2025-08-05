#set(CMAKE_PREFIX_PATH "C:/source/cadlib/3rdParty/v_32.0/Qt/x64/lib/cmake/Qt5" CACHE STRING "")
## -DCMAKE_PREFIX_PATH="C:/source/cadlib/3rdParty/v_32.0/Qt/x64/lib/cmake/Qt5"


set(CMAKE_PREFIX_PATH "C:/source/cadlib/3rdParty/v_32.0/Qt/x64/lib/cmake/Qt5" CACHE STRING "Prefix path for find_package" FORCE)
#message(STATUS "Prefix Path ${CMAKE_PREFIX_PATH}")

#if(DEFINED CMAKE_PREFIX_PATH)
#    list(APPEND CMAKE_PREFIX_PATH "C:/source/cadlib/3rdParty/v_32.0/Qt/x64/lib/cmake/Qt5")
#else()
#    set(CMAKE_PREFIX_PATH "C:/source/cadlib/3rdParty/v_32.0/Qt/x64/lib/cmake/Qt5")
#endif()
#
#message(STATUS "Prefix Path ${CMAKE_PREFIX_PATH}")

set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH}" CACHE STRING "Prefix path for find_package")
