cmake_minimum_required(VERSION 3.10)
project(C-CLI C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(include) 

add_executable(test_test 
	tests/unity.c
	tests/test_test.c
	src/debug_malloc.c
)

add_executable(test_lexer 
	tests/unity.c
	tests/test_lexer.c
	src/Lexer.c
	src/debug_malloc.c
)

add_executable(ccli
	src/main.c
)

set_target_properties(test_test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
set_target_properties(test_lexer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
set_target_properties(ccli PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

enable_testing()
add_test(NAME testTest COMMAND test_test)
add_test(NAME testLexer COMMAND test_lexer)


message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C compiler: ${CMAKE_C_COMPILER}")
