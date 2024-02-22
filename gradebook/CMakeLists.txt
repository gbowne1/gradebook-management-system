cmake_minimum_required(VERSION 3.14)

# Setup C++ standards
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_LIBRARY OFF CACHE STRING "Build project as a library")

# Copy CSV files
configure_file(assets/assignmentdata.csv assets/assignmentdata.csv COPYONLY)
configure_file(assets/classdata.csv assets/classdata.csv COPYONLY)
configure_file(assets/grades.csv assets/grades.csv COPYONLY)
configure_file(assets/studentdata.csv assets/studentdata.csv COPYONLY)
configure_file(assets/teacherdata.csv assets/teacherdata.csv COPYONLY)

# Define headers and sources
set(TARGET_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(TARGET_SOURCES  ${CMAKE_CURRENT_SOURCE_DIR}/source/gradebook.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/source/dataframe.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/source/permissions.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/source/exceptions.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/source/utils.cpp
)

# Support IDE visualization
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TARGET_SOURCES})

message(BUILD_LIBRARY ${BUILD_LIBRARY})
# Target executable/library
if(${BUILD_LIBRARY})
    add_library(${PROJECT_NAME} ${TARGET_SOURCES})
else()
    add_executable(${PROJECT_NAME}  ${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp 
                                    ${TARGET_SOURCES}
    )
endif()

# Include directories
target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/exports>
        ${TARGET_INCLUDE_DIR}
)
