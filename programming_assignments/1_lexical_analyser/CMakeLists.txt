cmake_minimum_required(VERSION 3.22.1)
project("etac")

find_package(GTest REQUIRED)

add_executable(etac main.cpp)
add_executable(lexer lex.yy.c)
target_link_libraries(etac ${GTEST_LIBRARIES})

enable_testing()
