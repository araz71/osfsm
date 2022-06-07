cmake_minimum_required(VERSION 2.8)
project(COMM_PROTOCOL_TEST)

include_directories("${CMAKE_CURRENT_SRC_DIR}src")
include_directories("${CMAKE_CURRENT_SRC_DIR}test")
set(SOURCES ${CMAKE_CURRENT_SRC_DIR}test/main.c ${CMAKE_CURRENT_SRC_DIR}src/danish.c)
message(${SOURCES})
add_executable(COMM_PROTOCOL_TEST ${SOURCES})
	

