cmake_minimum_required(VERSION 3.28)

project(http1.1)

include(CTest)

include_directories(${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/test)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS "-Wall -Wextra")

add_executable(
		${CMAKE_PROJECT_NAME} 
		src/main.c 
		src/char_array.c
		src/http_parser.c
		src/http_headers.c
		src/dealloc_http_request.c
)

add_executable(
		char_array_test 
		test/char_array_test.c
		src/char_array.c
)

add_executable(
		http_parser_test
		test/http_parser_test.c
		src/http_parser.c
		src/char_array.c
		src/dealloc_http_request.c
		src/http_headers.c
)

add_executable(
		http_response_test
		test/http_response_test.c
		src/http_response.c
		src/char_array.c
		src/dealloc_http_request.c
		src/http_headers.c
)

add_test(NAME TestCharArray COMMAND char_array_test)
add_test(NAME TestHttpParser COMMAND http_parser_test)
add_test(NAME TestHttpResponse COMMAND http_response_test)
