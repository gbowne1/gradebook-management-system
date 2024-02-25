cmake_minimum_required(VERSION 3.14)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Copy CSV files
configure_file(assets/assignmentdata.csv assets/assignmentdata.csv COPYONLY)
configure_file(assets/classdata.csv assets/classdata.csv COPYONLY)
configure_file(assets/grades.csv assets/grades.csv COPYONLY)
configure_file(assets/studentdata.csv assets/studentdata.csv COPYONLY)
configure_file(assets/teacherdata.csv assets/teacherdata.csv COPYONLY)

# Fetch GoogleTest library
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(TEST_BUNDLE ${PROJECT_NAME}_test)

set(TARGET_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB SOURCES_TESTS src/tests/*.cpp)
file(GLOB SOURCES_FIXTURES src/fixtures/*.cpp)

enable_testing()
# Compile all source files in this folder into one target--test bundle
add_executable(${TEST_BUNDLE} ${SOURCES_TESTS}
                              ${SOURCES_FIXTURES}
)

# Test include directories
target_include_directories(${TEST_BUNDLE}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/exports>
        ${TARGET_INCLUDE_DIR}
)

# Specify which targets the test bundle depends on
target_link_libraries(${TEST_BUNDLE} ${PROJECT_NAME} GTest::gtest_main)

# Include GoogleTest library
include(GoogleTest)
gtest_discover_tests(${TEST_BUNDLE})