cmake_minimum_required(VERSION 3.14)
project(gradebook)

# Setup C++ standards
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TESTING OFF CACHE STRING "Enable testing [ON/OFF]")

# Setup project
if(${TESTING})
    set(BUILD_LIBRARY ON)
    add_subdirectory(gradebook)
    add_subdirectory(tests)
else()
    add_subdirectory(gradebook)
endif()