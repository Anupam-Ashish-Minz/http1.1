cmake_minimum_required(VERSION 3.28)

project(http1.1)

include(CTest)

include_directories(${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/test)

set(CMAKE_BUILD_TYPE Debug)

add_executable(
		${CMAKE_PROJECT_NAME} 
		src/main.c 
		src/char_array.c
		src/http_parser.c
)

add_executable(
		char_array_test 
		test/char_array_test.c
		src/char_array.c
)

add_test(NAME TestCharArray COMMAND char_array_test)
