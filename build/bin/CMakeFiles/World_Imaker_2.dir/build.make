# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /media/msgro/Maxtor/World_Imaker/World_Imaker_merge/World_Imaker

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /media/msgro/Maxtor/World_Imaker/World_Imaker_merge/World_Imaker/build

# Include any dependencies generated for this target.
include bin/CMakeFiles/World_Imaker_2.dir/depend.make

# Include the progress variables for this target.
include bin/CMakeFiles/World_Imaker_2.dir/progress.make

# Include the compile flags for this target's objects.
include bin/CMakeFiles/World_Imaker_2.dir/flags.make

bin/CMakeFiles/World_Imaker_2.dir/main2.cpp.o: bin/CMakeFiles/World_Imaker_2.dir/flags.make
bin/CMakeFiles/World_Imaker_2.dir/main2.cpp.o: ../src/main2.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/msgro/Maxtor/World_Imaker/World_Imaker_merge/World_Imaker/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object bin/CMakeFiles/World_Imaker_2.dir/main2.cpp.o"
	cd /media/msgro/Maxtor/World_Imaker/World_Imaker_merge/World_Imaker/build/bin && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/World_Imaker_2.dir/main2.cpp.o -c /media/msgro/Maxtor/World_Imaker/World_Imaker_merge/World_Imaker/src/main2.cpp

bin/CMakeFiles/World_Imaker_2.dir/main2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/World_Imaker_2.dir/main2.cpp.i"
	cd /media/msgro/Maxtor/World_Imaker/World_Imaker_merge/World_Imaker/build/bin && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/msgro/Maxtor/World_Imaker/World_Imaker_merge/World_Imaker/src/main2.cpp > CMakeFiles/World_Imaker_2.dir/main2.cpp.i

bin/CMakeFiles/World_Imaker_2.dir/main2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/World_Imaker_2.dir/main2.cpp.s"
	cd /media/msgro/Maxtor/World_Imaker/World_Imaker_merge/World_Imaker/build/bin && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/msgro/Maxtor/World_Imaker/World_Imaker_merge/World_Imaker/src/main2.cpp -o CMakeFiles/World_Imaker_2.dir/main2.cpp.s

bin/CMakeFiles/World_Imaker_2.dir/main2.cpp.o.requires:

.PHONY : bin/CMakeFiles/World_Imaker_2.dir/main2.cpp.o.requires

bin/CMakeFiles/World_Imaker_2.dir/main2.cpp.o.provides: bin/CMakeFiles/World_Imaker_2.dir/main2.cpp.o.requires
	$(MAKE) -f bin/CMakeFiles/World_Imaker_2.dir/build.make bin/CMakeFiles/World_Imaker_2.dir/main2.cpp.o.provides.build
.PHONY : bin/CMakeFiles/World_Imaker_2.dir/main2.cpp.o.provides

bin/CMakeFiles/World_Imaker_2.dir/main2.cpp.o.provides.build: bin/CMakeFiles/World_Imaker_2.dir/main2.cpp.o


# Object files for target World_Imaker_2
World_Imaker_2_OBJECTS = \
"CMakeFiles/World_Imaker_2.dir/main2.cpp.o"

# External object files for target World_Imaker_2
World_Imaker_2_EXTERNAL_OBJECTS =

bin/World_Imaker_2: bin/CMakeFiles/World_Imaker_2.dir/main2.cpp.o
bin/World_Imaker_2: bin/CMakeFiles/World_Imaker_2.dir/build.make
bin/World_Imaker_2: glimac/libglimac.a
bin/World_Imaker_2: third-party/include/imgui/libimgui.a
bin/World_Imaker_2: /usr/lib/x86_64-linux-gnu/libGL.so
bin/World_Imaker_2: /usr/lib/x86_64-linux-gnu/libGLU.so
bin/World_Imaker_2: /usr/lib/x86_64-linux-gnu/libGLEW.so
bin/World_Imaker_2: bin/CMakeFiles/World_Imaker_2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/media/msgro/Maxtor/World_Imaker/World_Imaker_merge/World_Imaker/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable World_Imaker_2"
	cd /media/msgro/Maxtor/World_Imaker/World_Imaker_merge/World_Imaker/build/bin && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/World_Imaker_2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bin/CMakeFiles/World_Imaker_2.dir/build: bin/World_Imaker_2

.PHONY : bin/CMakeFiles/World_Imaker_2.dir/build

bin/CMakeFiles/World_Imaker_2.dir/requires: bin/CMakeFiles/World_Imaker_2.dir/main2.cpp.o.requires

.PHONY : bin/CMakeFiles/World_Imaker_2.dir/requires

bin/CMakeFiles/World_Imaker_2.dir/clean:
	cd /media/msgro/Maxtor/World_Imaker/World_Imaker_merge/World_Imaker/build/bin && $(CMAKE_COMMAND) -P CMakeFiles/World_Imaker_2.dir/cmake_clean.cmake
.PHONY : bin/CMakeFiles/World_Imaker_2.dir/clean

bin/CMakeFiles/World_Imaker_2.dir/depend:
	cd /media/msgro/Maxtor/World_Imaker/World_Imaker_merge/World_Imaker/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/msgro/Maxtor/World_Imaker/World_Imaker_merge/World_Imaker /media/msgro/Maxtor/World_Imaker/World_Imaker_merge/World_Imaker/src /media/msgro/Maxtor/World_Imaker/World_Imaker_merge/World_Imaker/build /media/msgro/Maxtor/World_Imaker/World_Imaker_merge/World_Imaker/build/bin /media/msgro/Maxtor/World_Imaker/World_Imaker_merge/World_Imaker/build/bin/CMakeFiles/World_Imaker_2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : bin/CMakeFiles/World_Imaker_2.dir/depend

