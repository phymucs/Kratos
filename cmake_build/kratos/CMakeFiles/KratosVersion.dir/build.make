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
CMAKE_SOURCE_DIR = /home/gabriela/Software/Kratos

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gabriela/Software/Kratos/cmake_build

# Include any dependencies generated for this target.
include kratos/CMakeFiles/KratosVersion.dir/depend.make

# Include the progress variables for this target.
include kratos/CMakeFiles/KratosVersion.dir/progress.make

# Include the compile flags for this target's objects.
include kratos/CMakeFiles/KratosVersion.dir/flags.make

kratos/CMakeFiles/KratosVersion.dir/sources/kratos_version.cpp.o: kratos/CMakeFiles/KratosVersion.dir/flags.make
kratos/CMakeFiles/KratosVersion.dir/sources/kratos_version.cpp.o: ../kratos/sources/kratos_version.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gabriela/Software/Kratos/cmake_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object kratos/CMakeFiles/KratosVersion.dir/sources/kratos_version.cpp.o"
	cd /home/gabriela/Software/Kratos/cmake_build/kratos && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/KratosVersion.dir/sources/kratos_version.cpp.o -c /home/gabriela/Software/Kratos/kratos/sources/kratos_version.cpp

kratos/CMakeFiles/KratosVersion.dir/sources/kratos_version.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KratosVersion.dir/sources/kratos_version.cpp.i"
	cd /home/gabriela/Software/Kratos/cmake_build/kratos && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gabriela/Software/Kratos/kratos/sources/kratos_version.cpp > CMakeFiles/KratosVersion.dir/sources/kratos_version.cpp.i

kratos/CMakeFiles/KratosVersion.dir/sources/kratos_version.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KratosVersion.dir/sources/kratos_version.cpp.s"
	cd /home/gabriela/Software/Kratos/cmake_build/kratos && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gabriela/Software/Kratos/kratos/sources/kratos_version.cpp -o CMakeFiles/KratosVersion.dir/sources/kratos_version.cpp.s

kratos/CMakeFiles/KratosVersion.dir/sources/kratos_version.cpp.o.requires:

.PHONY : kratos/CMakeFiles/KratosVersion.dir/sources/kratos_version.cpp.o.requires

kratos/CMakeFiles/KratosVersion.dir/sources/kratos_version.cpp.o.provides: kratos/CMakeFiles/KratosVersion.dir/sources/kratos_version.cpp.o.requires
	$(MAKE) -f kratos/CMakeFiles/KratosVersion.dir/build.make kratos/CMakeFiles/KratosVersion.dir/sources/kratos_version.cpp.o.provides.build
.PHONY : kratos/CMakeFiles/KratosVersion.dir/sources/kratos_version.cpp.o.provides

kratos/CMakeFiles/KratosVersion.dir/sources/kratos_version.cpp.o.provides.build: kratos/CMakeFiles/KratosVersion.dir/sources/kratos_version.cpp.o


KratosVersion: kratos/CMakeFiles/KratosVersion.dir/sources/kratos_version.cpp.o
KratosVersion: kratos/CMakeFiles/KratosVersion.dir/build.make

.PHONY : KratosVersion

# Rule to build all files generated by this target.
kratos/CMakeFiles/KratosVersion.dir/build: KratosVersion

.PHONY : kratos/CMakeFiles/KratosVersion.dir/build

kratos/CMakeFiles/KratosVersion.dir/requires: kratos/CMakeFiles/KratosVersion.dir/sources/kratos_version.cpp.o.requires

.PHONY : kratos/CMakeFiles/KratosVersion.dir/requires

kratos/CMakeFiles/KratosVersion.dir/clean:
	cd /home/gabriela/Software/Kratos/cmake_build/kratos && $(CMAKE_COMMAND) -P CMakeFiles/KratosVersion.dir/cmake_clean.cmake
.PHONY : kratos/CMakeFiles/KratosVersion.dir/clean

kratos/CMakeFiles/KratosVersion.dir/depend:
	cd /home/gabriela/Software/Kratos/cmake_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gabriela/Software/Kratos /home/gabriela/Software/Kratos/kratos /home/gabriela/Software/Kratos/cmake_build /home/gabriela/Software/Kratos/cmake_build/kratos /home/gabriela/Software/Kratos/cmake_build/kratos/CMakeFiles/KratosVersion.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : kratos/CMakeFiles/KratosVersion.dir/depend
