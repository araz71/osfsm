# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/amin/Projects/osfsm/osfsm

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/amin/Projects/osfsm/osfsm/build

# Include any dependencies generated for this target.
include CMakeFiles/osfsm.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/osfsm.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/osfsm.dir/flags.make

CMakeFiles/osfsm.dir/src/main.c.o: CMakeFiles/osfsm.dir/flags.make
CMakeFiles/osfsm.dir/src/main.c.o: ../src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/amin/Projects/osfsm/osfsm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/osfsm.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/osfsm.dir/src/main.c.o   -c /home/amin/Projects/osfsm/osfsm/src/main.c

CMakeFiles/osfsm.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/osfsm.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/amin/Projects/osfsm/osfsm/src/main.c > CMakeFiles/osfsm.dir/src/main.c.i

CMakeFiles/osfsm.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/osfsm.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/amin/Projects/osfsm/osfsm/src/main.c -o CMakeFiles/osfsm.dir/src/main.c.s

CMakeFiles/osfsm.dir/fsm/src/fsm.c.o: CMakeFiles/osfsm.dir/flags.make
CMakeFiles/osfsm.dir/fsm/src/fsm.c.o: ../fsm/src/fsm.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/amin/Projects/osfsm/osfsm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/osfsm.dir/fsm/src/fsm.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/osfsm.dir/fsm/src/fsm.c.o   -c /home/amin/Projects/osfsm/osfsm/fsm/src/fsm.c

CMakeFiles/osfsm.dir/fsm/src/fsm.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/osfsm.dir/fsm/src/fsm.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/amin/Projects/osfsm/osfsm/fsm/src/fsm.c > CMakeFiles/osfsm.dir/fsm/src/fsm.c.i

CMakeFiles/osfsm.dir/fsm/src/fsm.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/osfsm.dir/fsm/src/fsm.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/amin/Projects/osfsm/osfsm/fsm/src/fsm.c -o CMakeFiles/osfsm.dir/fsm/src/fsm.c.s

CMakeFiles/osfsm.dir/fsm/src/delay.c.o: CMakeFiles/osfsm.dir/flags.make
CMakeFiles/osfsm.dir/fsm/src/delay.c.o: ../fsm/src/delay.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/amin/Projects/osfsm/osfsm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/osfsm.dir/fsm/src/delay.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/osfsm.dir/fsm/src/delay.c.o   -c /home/amin/Projects/osfsm/osfsm/fsm/src/delay.c

CMakeFiles/osfsm.dir/fsm/src/delay.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/osfsm.dir/fsm/src/delay.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/amin/Projects/osfsm/osfsm/fsm/src/delay.c > CMakeFiles/osfsm.dir/fsm/src/delay.c.i

CMakeFiles/osfsm.dir/fsm/src/delay.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/osfsm.dir/fsm/src/delay.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/amin/Projects/osfsm/osfsm/fsm/src/delay.c -o CMakeFiles/osfsm.dir/fsm/src/delay.c.s

CMakeFiles/osfsm.dir/fsm/src/fifo.c.o: CMakeFiles/osfsm.dir/flags.make
CMakeFiles/osfsm.dir/fsm/src/fifo.c.o: ../fsm/src/fifo.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/amin/Projects/osfsm/osfsm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/osfsm.dir/fsm/src/fifo.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/osfsm.dir/fsm/src/fifo.c.o   -c /home/amin/Projects/osfsm/osfsm/fsm/src/fifo.c

CMakeFiles/osfsm.dir/fsm/src/fifo.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/osfsm.dir/fsm/src/fifo.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/amin/Projects/osfsm/osfsm/fsm/src/fifo.c > CMakeFiles/osfsm.dir/fsm/src/fifo.c.i

CMakeFiles/osfsm.dir/fsm/src/fifo.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/osfsm.dir/fsm/src/fifo.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/amin/Projects/osfsm/osfsm/fsm/src/fifo.c -o CMakeFiles/osfsm.dir/fsm/src/fifo.c.s

# Object files for target osfsm
osfsm_OBJECTS = \
"CMakeFiles/osfsm.dir/src/main.c.o" \
"CMakeFiles/osfsm.dir/fsm/src/fsm.c.o" \
"CMakeFiles/osfsm.dir/fsm/src/delay.c.o" \
"CMakeFiles/osfsm.dir/fsm/src/fifo.c.o"

# External object files for target osfsm
osfsm_EXTERNAL_OBJECTS =

osfsm: CMakeFiles/osfsm.dir/src/main.c.o
osfsm: CMakeFiles/osfsm.dir/fsm/src/fsm.c.o
osfsm: CMakeFiles/osfsm.dir/fsm/src/delay.c.o
osfsm: CMakeFiles/osfsm.dir/fsm/src/fifo.c.o
osfsm: CMakeFiles/osfsm.dir/build.make
osfsm: CMakeFiles/osfsm.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/amin/Projects/osfsm/osfsm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable osfsm"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/osfsm.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/osfsm.dir/build: osfsm

.PHONY : CMakeFiles/osfsm.dir/build

CMakeFiles/osfsm.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/osfsm.dir/cmake_clean.cmake
.PHONY : CMakeFiles/osfsm.dir/clean

CMakeFiles/osfsm.dir/depend:
	cd /home/amin/Projects/osfsm/osfsm/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/amin/Projects/osfsm/osfsm /home/amin/Projects/osfsm/osfsm /home/amin/Projects/osfsm/osfsm/build /home/amin/Projects/osfsm/osfsm/build /home/amin/Projects/osfsm/osfsm/build/CMakeFiles/osfsm.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/osfsm.dir/depend

