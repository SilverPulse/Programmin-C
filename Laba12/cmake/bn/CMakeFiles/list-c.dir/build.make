# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/Shaim/Desktop/Учеба/СибГути/Программирование/test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/Shaim/Desktop/Учеба/СибГути/Программирование/test/bn

# Include any dependencies generated for this target.
include CMakeFiles/list-c.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/list-c.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/list-c.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/list-c.dir/flags.make

CMakeFiles/list-c.dir/main.c.o: CMakeFiles/list-c.dir/flags.make
CMakeFiles/list-c.dir/main.c.o: ../main.c
CMakeFiles/list-c.dir/main.c.o: CMakeFiles/list-c.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Shaim/Desktop/Учеба/СибГути/Программирование/test/bn/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/list-c.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/list-c.dir/main.c.o -MF CMakeFiles/list-c.dir/main.c.o.d -o CMakeFiles/list-c.dir/main.c.o -c /mnt/c/Users/Shaim/Desktop/Учеба/СибГути/Программирование/test/main.c

CMakeFiles/list-c.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/list-c.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Shaim/Desktop/Учеба/СибГути/Программирование/test/main.c > CMakeFiles/list-c.dir/main.c.i

CMakeFiles/list-c.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/list-c.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Shaim/Desktop/Учеба/СибГути/Программирование/test/main.c -o CMakeFiles/list-c.dir/main.c.s

CMakeFiles/list-c.dir/list_files.c.o: CMakeFiles/list-c.dir/flags.make
CMakeFiles/list-c.dir/list_files.c.o: ../list_files.c
CMakeFiles/list-c.dir/list_files.c.o: CMakeFiles/list-c.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Shaim/Desktop/Учеба/СибГути/Программирование/test/bn/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/list-c.dir/list_files.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/list-c.dir/list_files.c.o -MF CMakeFiles/list-c.dir/list_files.c.o.d -o CMakeFiles/list-c.dir/list_files.c.o -c /mnt/c/Users/Shaim/Desktop/Учеба/СибГути/Программирование/test/list_files.c

CMakeFiles/list-c.dir/list_files.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/list-c.dir/list_files.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Shaim/Desktop/Учеба/СибГути/Программирование/test/list_files.c > CMakeFiles/list-c.dir/list_files.c.i

CMakeFiles/list-c.dir/list_files.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/list-c.dir/list_files.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Shaim/Desktop/Учеба/СибГути/Программирование/test/list_files.c -o CMakeFiles/list-c.dir/list_files.c.s

# Object files for target list-c
list__c_OBJECTS = \
"CMakeFiles/list-c.dir/main.c.o" \
"CMakeFiles/list-c.dir/list_files.c.o"

# External object files for target list-c
list__c_EXTERNAL_OBJECTS =

list-c: CMakeFiles/list-c.dir/main.c.o
list-c: CMakeFiles/list-c.dir/list_files.c.o
list-c: CMakeFiles/list-c.dir/build.make
list-c: CMakeFiles/list-c.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/Shaim/Desktop/Учеба/СибГути/Программирование/test/bn/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable list-c"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/list-c.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/list-c.dir/build: list-c
.PHONY : CMakeFiles/list-c.dir/build

CMakeFiles/list-c.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/list-c.dir/cmake_clean.cmake
.PHONY : CMakeFiles/list-c.dir/clean

CMakeFiles/list-c.dir/depend:
	cd /mnt/c/Users/Shaim/Desktop/Учеба/СибГути/Программирование/test/bn && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Shaim/Desktop/Учеба/СибГути/Программирование/test /mnt/c/Users/Shaim/Desktop/Учеба/СибГути/Программирование/test /mnt/c/Users/Shaim/Desktop/Учеба/СибГути/Программирование/test/bn /mnt/c/Users/Shaim/Desktop/Учеба/СибГути/Программирование/test/bn /mnt/c/Users/Shaim/Desktop/Учеба/СибГути/Программирование/test/bn/CMakeFiles/list-c.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/list-c.dir/depend

