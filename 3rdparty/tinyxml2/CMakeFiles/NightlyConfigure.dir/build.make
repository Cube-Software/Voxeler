# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_SOURCE_DIR = /home/kacperks/Pulpit/Projects/Voxeler

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kacperks/Pulpit/Projects/Voxeler

# Utility rule file for NightlyConfigure.

# Include the progress variables for this target.
include 3rdparty/tinyxml2/CMakeFiles/NightlyConfigure.dir/progress.make

3rdparty/tinyxml2/CMakeFiles/NightlyConfigure:
	cd /home/kacperks/Pulpit/Projects/Voxeler/3rdparty/tinyxml2 && /usr/bin/ctest -D NightlyConfigure

NightlyConfigure: 3rdparty/tinyxml2/CMakeFiles/NightlyConfigure
NightlyConfigure: 3rdparty/tinyxml2/CMakeFiles/NightlyConfigure.dir/build.make

.PHONY : NightlyConfigure

# Rule to build all files generated by this target.
3rdparty/tinyxml2/CMakeFiles/NightlyConfigure.dir/build: NightlyConfigure

.PHONY : 3rdparty/tinyxml2/CMakeFiles/NightlyConfigure.dir/build

3rdparty/tinyxml2/CMakeFiles/NightlyConfigure.dir/clean:
	cd /home/kacperks/Pulpit/Projects/Voxeler/3rdparty/tinyxml2 && $(CMAKE_COMMAND) -P CMakeFiles/NightlyConfigure.dir/cmake_clean.cmake
.PHONY : 3rdparty/tinyxml2/CMakeFiles/NightlyConfigure.dir/clean

3rdparty/tinyxml2/CMakeFiles/NightlyConfigure.dir/depend:
	cd /home/kacperks/Pulpit/Projects/Voxeler && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kacperks/Pulpit/Projects/Voxeler /home/kacperks/Pulpit/Projects/Voxeler/3rdparty/tinyxml2 /home/kacperks/Pulpit/Projects/Voxeler /home/kacperks/Pulpit/Projects/Voxeler/3rdparty/tinyxml2 /home/kacperks/Pulpit/Projects/Voxeler/3rdparty/tinyxml2/CMakeFiles/NightlyConfigure.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : 3rdparty/tinyxml2/CMakeFiles/NightlyConfigure.dir/depend

