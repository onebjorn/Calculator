cmake_minimum_required(VERSION 2.8)

add_definitions(--std=c++11)

project(parser)
add_executable(${PROJECT_NAME} "main.cpp" "expression.h" "parser.h")


# Add subdirectory with Google Test Library.
add_subdirectory(3party/googletest)

# Enable unit testing.
enable_testing()
# Set up testing project name.
set(PROJECT_TEST_NAME ${PROJECT_NAME}_test)
# Add include directories for testing project.
include_directories(3party/googletest/googletest/include ${SOURCE_ROOT})
# Set up testing project.
set(TESTS_SOURCE_ROOT tests)
aux_source_directory(${TESTS_SOURCE_ROOT} TEST_SRC_FILES)
set(TEST_SRC_FILES ${PROJECT_NAME} ${TEST_SRC_FILES})
list(REMOVE_ITEM TEST_SRC_FILES main.cpp)
add_executable(${PROJECT_TEST_NAME} ${TEST_SRC_FILES})
# Link gtest and gtest_main libraries.
target_link_libraries(${PROJECT_TEST_NAME} gtest gtest_main)
# Finish tests setting up.
add_test(test ${PROJECT_TEST_NAME})
