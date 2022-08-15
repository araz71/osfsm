cmake_minimum_required(VERSION 2.8)
project(LINK_TEST)


include_directories("../../inc")
include_directories("../../../fsm/inc")

set(SOURCES main.c ../../src/danish.c
	../../src/danish_link.c
	../../../fsm/src/delay.c)

message(${SOURCES})
add_executable(LINK ${SOURCES})
	

