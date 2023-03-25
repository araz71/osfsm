cmake_minimum_required(VERSION 2.1)

PROJECT(EXAMPLES)

INCLUDE_DIRECTORIES("src" "examples")

SET(SOURCES "src/fsm.c"
	"src/delay.c")

add_compile_definitions(MY_DELAY)
ADD_EXECUTABLE(FSM examples/ex_fsm.c ${SOURCES})
