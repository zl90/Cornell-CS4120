cmake_minimum_required(VERSION 3.22.1)
project("etac")

find_package(GTest REQUIRED)

# Define a custom command to run flex and generate lex.yy.c
add_custom_command(
    OUTPUT lex.yy.c
    COMMAND flex ${CMAKE_CURRENT_SOURCE_DIR}/flex_input.l
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/flex_input.l
    COMMENT "Running flex on flex_input.l"
)

# Create the etac executable with the lexer as a source file
add_executable(lexer lex.yy.c)
add_executable(etac main.cpp)

target_link_libraries(etac ${GTEST_LIBRARIES})

enable_testing()