cmake_minimum_required(VERSION 2.1)

PROJECT(EXAMPLES)

INCLUDE_DIRECTORIES(../src ${CMAKE_SOURCE_DIR})

SET(SOURCES "../src/fsm.c"
	"../src/delay.c")
add_compile_definitions(MY_DELAY)
ADD_EXECUTABLE(FSM ex_fsm.c ${SOURCES})
