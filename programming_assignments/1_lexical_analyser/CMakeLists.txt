cmake_minimum_required(VERSION 3.22.1)
project("etac")

find_package(GTest REQUIRED)

# Define the target for running flex
add_custom_target(run_flex
    COMMAND flex flex_input.l
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Running flex on flex_input.l"
)

# Create the etac executable with the lexer as a source file
add_executable(lexer lex.yy.c)
add_executable(etac main.cpp)

# Add main.cpp as a dependency of the run_flex target
add_dependencies(run_flex etac)

target_link_libraries(etac ${GTEST_LIBRARIES})

enable_testing()