# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/renlide/Projects/Graph_Paritioning/Naive_Greedy

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/renlide/Projects/Graph_Paritioning/Naive_Greedy/build

# Include any dependencies generated for this target.
include CMakeFiles/NG.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/NG.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/NG.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/NG.dir/flags.make

CMakeFiles/NG.dir/src/NG.cpp.o: CMakeFiles/NG.dir/flags.make
CMakeFiles/NG.dir/src/NG.cpp.o: ../src/NG.cpp
CMakeFiles/NG.dir/src/NG.cpp.o: CMakeFiles/NG.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/renlide/Projects/Graph_Paritioning/Naive_Greedy/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/NG.dir/src/NG.cpp.o"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NG.dir/src/NG.cpp.o -MF CMakeFiles/NG.dir/src/NG.cpp.o.d -o CMakeFiles/NG.dir/src/NG.cpp.o -c /Users/renlide/Projects/Graph_Paritioning/Naive_Greedy/src/NG.cpp

CMakeFiles/NG.dir/src/NG.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NG.dir/src/NG.cpp.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/renlide/Projects/Graph_Paritioning/Naive_Greedy/src/NG.cpp > CMakeFiles/NG.dir/src/NG.cpp.i

CMakeFiles/NG.dir/src/NG.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NG.dir/src/NG.cpp.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/renlide/Projects/Graph_Paritioning/Naive_Greedy/src/NG.cpp -o CMakeFiles/NG.dir/src/NG.cpp.s

CMakeFiles/NG.dir/src/block.cpp.o: CMakeFiles/NG.dir/flags.make
CMakeFiles/NG.dir/src/block.cpp.o: ../src/block.cpp
CMakeFiles/NG.dir/src/block.cpp.o: CMakeFiles/NG.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/renlide/Projects/Graph_Paritioning/Naive_Greedy/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/NG.dir/src/block.cpp.o"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NG.dir/src/block.cpp.o -MF CMakeFiles/NG.dir/src/block.cpp.o.d -o CMakeFiles/NG.dir/src/block.cpp.o -c /Users/renlide/Projects/Graph_Paritioning/Naive_Greedy/src/block.cpp

CMakeFiles/NG.dir/src/block.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NG.dir/src/block.cpp.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/renlide/Projects/Graph_Paritioning/Naive_Greedy/src/block.cpp > CMakeFiles/NG.dir/src/block.cpp.i

CMakeFiles/NG.dir/src/block.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NG.dir/src/block.cpp.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/renlide/Projects/Graph_Paritioning/Naive_Greedy/src/block.cpp -o CMakeFiles/NG.dir/src/block.cpp.s

CMakeFiles/NG.dir/src/graph.cpp.o: CMakeFiles/NG.dir/flags.make
CMakeFiles/NG.dir/src/graph.cpp.o: ../src/graph.cpp
CMakeFiles/NG.dir/src/graph.cpp.o: CMakeFiles/NG.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/renlide/Projects/Graph_Paritioning/Naive_Greedy/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/NG.dir/src/graph.cpp.o"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NG.dir/src/graph.cpp.o -MF CMakeFiles/NG.dir/src/graph.cpp.o.d -o CMakeFiles/NG.dir/src/graph.cpp.o -c /Users/renlide/Projects/Graph_Paritioning/Naive_Greedy/src/graph.cpp

CMakeFiles/NG.dir/src/graph.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NG.dir/src/graph.cpp.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/renlide/Projects/Graph_Paritioning/Naive_Greedy/src/graph.cpp > CMakeFiles/NG.dir/src/graph.cpp.i

CMakeFiles/NG.dir/src/graph.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NG.dir/src/graph.cpp.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/renlide/Projects/Graph_Paritioning/Naive_Greedy/src/graph.cpp -o CMakeFiles/NG.dir/src/graph.cpp.s

CMakeFiles/NG.dir/src/main.cpp.o: CMakeFiles/NG.dir/flags.make
CMakeFiles/NG.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/NG.dir/src/main.cpp.o: CMakeFiles/NG.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/renlide/Projects/Graph_Paritioning/Naive_Greedy/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/NG.dir/src/main.cpp.o"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NG.dir/src/main.cpp.o -MF CMakeFiles/NG.dir/src/main.cpp.o.d -o CMakeFiles/NG.dir/src/main.cpp.o -c /Users/renlide/Projects/Graph_Paritioning/Naive_Greedy/src/main.cpp

CMakeFiles/NG.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NG.dir/src/main.cpp.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/renlide/Projects/Graph_Paritioning/Naive_Greedy/src/main.cpp > CMakeFiles/NG.dir/src/main.cpp.i

CMakeFiles/NG.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NG.dir/src/main.cpp.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/renlide/Projects/Graph_Paritioning/Naive_Greedy/src/main.cpp -o CMakeFiles/NG.dir/src/main.cpp.s

CMakeFiles/NG.dir/src/point.cpp.o: CMakeFiles/NG.dir/flags.make
CMakeFiles/NG.dir/src/point.cpp.o: ../src/point.cpp
CMakeFiles/NG.dir/src/point.cpp.o: CMakeFiles/NG.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/renlide/Projects/Graph_Paritioning/Naive_Greedy/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/NG.dir/src/point.cpp.o"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NG.dir/src/point.cpp.o -MF CMakeFiles/NG.dir/src/point.cpp.o.d -o CMakeFiles/NG.dir/src/point.cpp.o -c /Users/renlide/Projects/Graph_Paritioning/Naive_Greedy/src/point.cpp

CMakeFiles/NG.dir/src/point.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NG.dir/src/point.cpp.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/renlide/Projects/Graph_Paritioning/Naive_Greedy/src/point.cpp > CMakeFiles/NG.dir/src/point.cpp.i

CMakeFiles/NG.dir/src/point.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NG.dir/src/point.cpp.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/renlide/Projects/Graph_Paritioning/Naive_Greedy/src/point.cpp -o CMakeFiles/NG.dir/src/point.cpp.s

# Object files for target NG
NG_OBJECTS = \
"CMakeFiles/NG.dir/src/NG.cpp.o" \
"CMakeFiles/NG.dir/src/block.cpp.o" \
"CMakeFiles/NG.dir/src/graph.cpp.o" \
"CMakeFiles/NG.dir/src/main.cpp.o" \
"CMakeFiles/NG.dir/src/point.cpp.o"

# External object files for target NG
NG_EXTERNAL_OBJECTS =

NG: CMakeFiles/NG.dir/src/NG.cpp.o
NG: CMakeFiles/NG.dir/src/block.cpp.o
NG: CMakeFiles/NG.dir/src/graph.cpp.o
NG: CMakeFiles/NG.dir/src/main.cpp.o
NG: CMakeFiles/NG.dir/src/point.cpp.o
NG: CMakeFiles/NG.dir/build.make
NG: CMakeFiles/NG.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/renlide/Projects/Graph_Paritioning/Naive_Greedy/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable NG"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/NG.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/NG.dir/build: NG
.PHONY : CMakeFiles/NG.dir/build

CMakeFiles/NG.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/NG.dir/cmake_clean.cmake
.PHONY : CMakeFiles/NG.dir/clean

CMakeFiles/NG.dir/depend:
	cd /Users/renlide/Projects/Graph_Paritioning/Naive_Greedy/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/renlide/Projects/Graph_Paritioning/Naive_Greedy /Users/renlide/Projects/Graph_Paritioning/Naive_Greedy /Users/renlide/Projects/Graph_Paritioning/Naive_Greedy/build /Users/renlide/Projects/Graph_Paritioning/Naive_Greedy/build /Users/renlide/Projects/Graph_Paritioning/Naive_Greedy/build/CMakeFiles/NG.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/NG.dir/depend
