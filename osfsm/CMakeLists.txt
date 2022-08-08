cmake_minimum_required(VERSION 2.8)

project(osfsm LANGUAGES C)
set(SOURCES src/main.c
		fsm/src/fsm.c
		fsm/src/delay.c
		fsm/src/fifo.c
		fsm/src/shm.c)

include_directories("fsm/inc")

add_executable(osfsm ${SOURCES})

add_subdirectory(comm_protocol)


