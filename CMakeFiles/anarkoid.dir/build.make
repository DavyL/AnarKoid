# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_SOURCE_DIR = /home/sf/Prog/AnarKoid

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sf/Prog/AnarKoid

# Include any dependencies generated for this target.
include CMakeFiles/anarkoid.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/anarkoid.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/anarkoid.dir/flags.make

CMakeFiles/anarkoid.dir/src/GLutils.c.o: CMakeFiles/anarkoid.dir/flags.make
CMakeFiles/anarkoid.dir/src/GLutils.c.o: src/GLutils.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sf/Prog/AnarKoid/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/anarkoid.dir/src/GLutils.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/anarkoid.dir/src/GLutils.c.o   -c /home/sf/Prog/AnarKoid/src/GLutils.c

CMakeFiles/anarkoid.dir/src/GLutils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/anarkoid.dir/src/GLutils.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/sf/Prog/AnarKoid/src/GLutils.c > CMakeFiles/anarkoid.dir/src/GLutils.c.i

CMakeFiles/anarkoid.dir/src/GLutils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/anarkoid.dir/src/GLutils.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/sf/Prog/AnarKoid/src/GLutils.c -o CMakeFiles/anarkoid.dir/src/GLutils.c.s

CMakeFiles/anarkoid.dir/src/common.c.o: CMakeFiles/anarkoid.dir/flags.make
CMakeFiles/anarkoid.dir/src/common.c.o: src/common.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sf/Prog/AnarKoid/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/anarkoid.dir/src/common.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/anarkoid.dir/src/common.c.o   -c /home/sf/Prog/AnarKoid/src/common.c

CMakeFiles/anarkoid.dir/src/common.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/anarkoid.dir/src/common.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/sf/Prog/AnarKoid/src/common.c > CMakeFiles/anarkoid.dir/src/common.c.i

CMakeFiles/anarkoid.dir/src/common.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/anarkoid.dir/src/common.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/sf/Prog/AnarKoid/src/common.c -o CMakeFiles/anarkoid.dir/src/common.c.s

CMakeFiles/anarkoid.dir/src/draw.c.o: CMakeFiles/anarkoid.dir/flags.make
CMakeFiles/anarkoid.dir/src/draw.c.o: src/draw.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sf/Prog/AnarKoid/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/anarkoid.dir/src/draw.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/anarkoid.dir/src/draw.c.o   -c /home/sf/Prog/AnarKoid/src/draw.c

CMakeFiles/anarkoid.dir/src/draw.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/anarkoid.dir/src/draw.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/sf/Prog/AnarKoid/src/draw.c > CMakeFiles/anarkoid.dir/src/draw.c.i

CMakeFiles/anarkoid.dir/src/draw.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/anarkoid.dir/src/draw.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/sf/Prog/AnarKoid/src/draw.c -o CMakeFiles/anarkoid.dir/src/draw.c.s

CMakeFiles/anarkoid.dir/src/main.c.o: CMakeFiles/anarkoid.dir/flags.make
CMakeFiles/anarkoid.dir/src/main.c.o: src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sf/Prog/AnarKoid/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/anarkoid.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/anarkoid.dir/src/main.c.o   -c /home/sf/Prog/AnarKoid/src/main.c

CMakeFiles/anarkoid.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/anarkoid.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/sf/Prog/AnarKoid/src/main.c > CMakeFiles/anarkoid.dir/src/main.c.i

CMakeFiles/anarkoid.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/anarkoid.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/sf/Prog/AnarKoid/src/main.c -o CMakeFiles/anarkoid.dir/src/main.c.s

CMakeFiles/anarkoid.dir/src/matrixUtils.c.o: CMakeFiles/anarkoid.dir/flags.make
CMakeFiles/anarkoid.dir/src/matrixUtils.c.o: src/matrixUtils.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sf/Prog/AnarKoid/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/anarkoid.dir/src/matrixUtils.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/anarkoid.dir/src/matrixUtils.c.o   -c /home/sf/Prog/AnarKoid/src/matrixUtils.c

CMakeFiles/anarkoid.dir/src/matrixUtils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/anarkoid.dir/src/matrixUtils.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/sf/Prog/AnarKoid/src/matrixUtils.c > CMakeFiles/anarkoid.dir/src/matrixUtils.c.i

CMakeFiles/anarkoid.dir/src/matrixUtils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/anarkoid.dir/src/matrixUtils.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/sf/Prog/AnarKoid/src/matrixUtils.c -o CMakeFiles/anarkoid.dir/src/matrixUtils.c.s

CMakeFiles/anarkoid.dir/src/util.c.o: CMakeFiles/anarkoid.dir/flags.make
CMakeFiles/anarkoid.dir/src/util.c.o: src/util.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sf/Prog/AnarKoid/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/anarkoid.dir/src/util.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/anarkoid.dir/src/util.c.o   -c /home/sf/Prog/AnarKoid/src/util.c

CMakeFiles/anarkoid.dir/src/util.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/anarkoid.dir/src/util.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/sf/Prog/AnarKoid/src/util.c > CMakeFiles/anarkoid.dir/src/util.c.i

CMakeFiles/anarkoid.dir/src/util.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/anarkoid.dir/src/util.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/sf/Prog/AnarKoid/src/util.c -o CMakeFiles/anarkoid.dir/src/util.c.s

# Object files for target anarkoid
anarkoid_OBJECTS = \
"CMakeFiles/anarkoid.dir/src/GLutils.c.o" \
"CMakeFiles/anarkoid.dir/src/common.c.o" \
"CMakeFiles/anarkoid.dir/src/draw.c.o" \
"CMakeFiles/anarkoid.dir/src/main.c.o" \
"CMakeFiles/anarkoid.dir/src/matrixUtils.c.o" \
"CMakeFiles/anarkoid.dir/src/util.c.o"

# External object files for target anarkoid
anarkoid_EXTERNAL_OBJECTS =

anarkoid: CMakeFiles/anarkoid.dir/src/GLutils.c.o
anarkoid: CMakeFiles/anarkoid.dir/src/common.c.o
anarkoid: CMakeFiles/anarkoid.dir/src/draw.c.o
anarkoid: CMakeFiles/anarkoid.dir/src/main.c.o
anarkoid: CMakeFiles/anarkoid.dir/src/matrixUtils.c.o
anarkoid: CMakeFiles/anarkoid.dir/src/util.c.o
anarkoid: CMakeFiles/anarkoid.dir/build.make
anarkoid: /usr/lib/x86_64-linux-gnu/libOpenGL.so
anarkoid: /usr/lib/x86_64-linux-gnu/libGLX.so
anarkoid: /usr/lib/x86_64-linux-gnu/libGLU.so
anarkoid: /usr/lib/x86_64-linux-gnu/libglut.so
anarkoid: /usr/lib/x86_64-linux-gnu/libGLEW.so
anarkoid: CMakeFiles/anarkoid.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sf/Prog/AnarKoid/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking C executable anarkoid"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/anarkoid.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/anarkoid.dir/build: anarkoid

.PHONY : CMakeFiles/anarkoid.dir/build

CMakeFiles/anarkoid.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/anarkoid.dir/cmake_clean.cmake
.PHONY : CMakeFiles/anarkoid.dir/clean

CMakeFiles/anarkoid.dir/depend:
	cd /home/sf/Prog/AnarKoid && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sf/Prog/AnarKoid /home/sf/Prog/AnarKoid /home/sf/Prog/AnarKoid /home/sf/Prog/AnarKoid /home/sf/Prog/AnarKoid/CMakeFiles/anarkoid.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/anarkoid.dir/depend

