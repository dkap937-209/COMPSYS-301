# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.2.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.2.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\darpa\OneDrive\Desktop\Uni\Part 3\Semester 2\COMPSYS 301\Path finding algorithm\Astar"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\darpa\OneDrive\Desktop\Uni\Part 3\Semester 2\COMPSYS 301\Path finding algorithm\Astar\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Astar.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/Astar.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Astar.dir/flags.make

CMakeFiles/Astar.dir/A_Star.cpp.obj: CMakeFiles/Astar.dir/flags.make
CMakeFiles/Astar.dir/A_Star.cpp.obj: ../A_Star.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\darpa\OneDrive\Desktop\Uni\Part 3\Semester 2\COMPSYS 301\Path finding algorithm\Astar\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Astar.dir/A_Star.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Astar.dir\A_Star.cpp.obj -c "C:\Users\darpa\OneDrive\Desktop\Uni\Part 3\Semester 2\COMPSYS 301\Path finding algorithm\Astar\A_Star.cpp"

CMakeFiles/Astar.dir/A_Star.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Astar.dir/A_Star.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\darpa\OneDrive\Desktop\Uni\Part 3\Semester 2\COMPSYS 301\Path finding algorithm\Astar\A_Star.cpp" > CMakeFiles\Astar.dir\A_Star.cpp.i

CMakeFiles/Astar.dir/A_Star.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Astar.dir/A_Star.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\darpa\OneDrive\Desktop\Uni\Part 3\Semester 2\COMPSYS 301\Path finding algorithm\Astar\A_Star.cpp" -o CMakeFiles\Astar.dir\A_Star.cpp.s

CMakeFiles/Astar.dir/helperFunctions.cpp.obj: CMakeFiles/Astar.dir/flags.make
CMakeFiles/Astar.dir/helperFunctions.cpp.obj: ../helperFunctions.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\darpa\OneDrive\Desktop\Uni\Part 3\Semester 2\COMPSYS 301\Path finding algorithm\Astar\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Astar.dir/helperFunctions.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Astar.dir\helperFunctions.cpp.obj -c "C:\Users\darpa\OneDrive\Desktop\Uni\Part 3\Semester 2\COMPSYS 301\Path finding algorithm\Astar\helperFunctions.cpp"

CMakeFiles/Astar.dir/helperFunctions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Astar.dir/helperFunctions.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\darpa\OneDrive\Desktop\Uni\Part 3\Semester 2\COMPSYS 301\Path finding algorithm\Astar\helperFunctions.cpp" > CMakeFiles\Astar.dir\helperFunctions.cpp.i

CMakeFiles/Astar.dir/helperFunctions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Astar.dir/helperFunctions.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\darpa\OneDrive\Desktop\Uni\Part 3\Semester 2\COMPSYS 301\Path finding algorithm\Astar\helperFunctions.cpp" -o CMakeFiles\Astar.dir\helperFunctions.cpp.s

# Object files for target Astar
Astar_OBJECTS = \
"CMakeFiles/Astar.dir/A_Star.cpp.obj" \
"CMakeFiles/Astar.dir/helperFunctions.cpp.obj"

# External object files for target Astar
Astar_EXTERNAL_OBJECTS =

Astar.exe: CMakeFiles/Astar.dir/A_Star.cpp.obj
Astar.exe: CMakeFiles/Astar.dir/helperFunctions.cpp.obj
Astar.exe: CMakeFiles/Astar.dir/build.make
Astar.exe: CMakeFiles/Astar.dir/linklibs.rsp
Astar.exe: CMakeFiles/Astar.dir/objects1.rsp
Astar.exe: CMakeFiles/Astar.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\darpa\OneDrive\Desktop\Uni\Part 3\Semester 2\COMPSYS 301\Path finding algorithm\Astar\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Astar.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Astar.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Astar.dir/build: Astar.exe
.PHONY : CMakeFiles/Astar.dir/build

CMakeFiles/Astar.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Astar.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Astar.dir/clean

CMakeFiles/Astar.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\darpa\OneDrive\Desktop\Uni\Part 3\Semester 2\COMPSYS 301\Path finding algorithm\Astar" "C:\Users\darpa\OneDrive\Desktop\Uni\Part 3\Semester 2\COMPSYS 301\Path finding algorithm\Astar" "C:\Users\darpa\OneDrive\Desktop\Uni\Part 3\Semester 2\COMPSYS 301\Path finding algorithm\Astar\cmake-build-debug" "C:\Users\darpa\OneDrive\Desktop\Uni\Part 3\Semester 2\COMPSYS 301\Path finding algorithm\Astar\cmake-build-debug" "C:\Users\darpa\OneDrive\Desktop\Uni\Part 3\Semester 2\COMPSYS 301\Path finding algorithm\Astar\cmake-build-debug\CMakeFiles\Astar.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Astar.dir/depend
