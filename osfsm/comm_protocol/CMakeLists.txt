cmake_minimum_required(VERSION 2.8)
project(COMM_PROTOCOL_TEST)


include_directories("${CMAKE_CURRENT_SRC_DIR}inc")
include_directories("${CMAKE_CURRENT_SRC_DIR}test")
include_directories("../fsm/inc")

add_subdirectory("test/link")

set(SOURCES ${CMAKE_CURRENT_SRC_DIR}test/main.c ${CMAKE_CURRENT_SRC_DIR}src/danish.c 
	../fsm/src/delay.c)
message(${SOURCES})
add_executable(COMM_PROTOCOL_TEST ${SOURCES})
	

