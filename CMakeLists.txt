cmake_minimum_required(VERSION 3.10)
project(C-CLI C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(include) 

add_executable(test_test 
	tests/unity.c
	tests/test_test.c
)

set_target_properties(test_test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
add_test(NAME testTest COMMAND test_test)


message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C compiler: ${CMAKE_C_COMPILER}")
