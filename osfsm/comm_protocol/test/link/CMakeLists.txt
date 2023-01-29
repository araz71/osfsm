cmake_minimum_required(VERSION 2.8)
project(LINK_TEST)

include_directories("../../src")
include_directories("../../../fsm/src")

set(SOURCES main.c ../../src/danish.c
	../../src/danish_link.c
	../../../fsm/src/delay.c)

add_executable(LINK ${SOURCES})
	

