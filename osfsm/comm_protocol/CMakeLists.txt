cmake_minimum_required(VERSION 2.8)
project(COMM_PROTOCOL_TEST)


include_directories("${CMAKE_CURRENT_SRC_DIR}src")
include_directories("${CMAKE_CURRENT_SRC_DIR}test")
include_directories("../fsm/inc")

add_subdirectory("test/link")
