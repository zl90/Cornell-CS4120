cmake_minimum_required(VERSION 3.22.1)
project("etac")

find_package(GTest REQUIRED)

# Create the build directory if it doesn't exist
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)

# Define a custom command to run flex and generate lex.yy.c
add_custom_command(
    OUTPUT lex.yy.c
    COMMAND flex ${CMAKE_CURRENT_SOURCE_DIR}/flex_input.l
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/flex_input.l
    COMMENT "Running flex on flex_input.l"
)

# Define a custom command to run bison
add_custom_command(
    OUTPUT bison_input.tab.c
    COMMAND bison -d -t -Wcounterexamples ${CMAKE_CURRENT_SOURCE_DIR}/bison_input.y
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/bison_input.y
    COMMENT "Running bison on bison_input.y"
)

# # Define a custom command to run bison
# add_custom_command(
#     OUTPUT bison_input.tab.c
#     COMMAND bison -d -t ${CMAKE_CURRENT_SOURCE_DIR}/bison_input.y
#     DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/bison_input.y
#     COMMENT "Running bison on bison_input.y"
# )

# Define a custom command to run flex
add_custom_command(
    OUTPUT bison.yy.c
    COMMAND flex -o ${CMAKE_CURRENT_SOURCE_DIR}/build/bison.yy.c ${CMAKE_CURRENT_SOURCE_DIR}/bison_input.l 
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/build/bison_input.tab.h
    COMMENT "Running flex on bison_input.l"
)

# Create the etac executable with the lexer as a source file
add_executable(lexer lex.yy.c)
add_executable(parser bison.yy.c bison_input.tab.c)
add_executable(etac main.cpp)

target_link_libraries(etac ${GTEST_LIBRARIES})

enable_testing()