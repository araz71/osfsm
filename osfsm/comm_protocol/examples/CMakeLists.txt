cmake_minimum_required(VERSION 2.18)

project (EXAMPLES)

include_directories("../../fsm/inc")
include_directories("../src")

add_executable(SENSOR ex1/sensor.c 
	../src/danish_link.c
	../src/danish.c
	../../fsm/src/delay.c)
