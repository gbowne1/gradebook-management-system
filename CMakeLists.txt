cmake_minimum_required(VERSION 3.14)

project(gradebook)

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
)

# Support IDE visualization
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TARGET_SOURCES})

# Target executable
add_executable(${PROJECT_NAME} ${TARGET_SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/exports>
    PRIVATE 
        ${TARGET_INCLUDE_DIR}
)