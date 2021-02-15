cmake_minimum_required(VERSION 3.10.0)

find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(test_factorial test_factorial.cc)
target_link_libraries(test_factorial factorial GTest::GTest GTest::Main)
include_directories(${PROJECT_SOURCE_DIR}/src ${GTEST_INCLUDE_DIRS})

gtest_discover_tests(test_factorial)
