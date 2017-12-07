cmake_minimum_required(VERSION 2.8)

add_definitions(--std=c++11)

project(parser)
add_executable(${PROJECT_NAME} "main.cpp" "expression.h" "parser.h")
