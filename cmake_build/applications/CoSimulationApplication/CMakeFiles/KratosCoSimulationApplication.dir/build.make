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
include applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/depend.make

# Include the progress variables for this target.
include applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/progress.make

# Include the compile flags for this target's objects.
include applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/flags.make

applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/co_simulation_application.cpp.o: applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/flags.make
applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/co_simulation_application.cpp.o: ../applications/CoSimulationApplication/co_simulation_application.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gabriela/Software/Kratos/cmake_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/co_simulation_application.cpp.o"
	cd /home/gabriela/Software/Kratos/cmake_build/applications/CoSimulationApplication && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/KratosCoSimulationApplication.dir/co_simulation_application.cpp.o -c /home/gabriela/Software/Kratos/applications/CoSimulationApplication/co_simulation_application.cpp

applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/co_simulation_application.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KratosCoSimulationApplication.dir/co_simulation_application.cpp.i"
	cd /home/gabriela/Software/Kratos/cmake_build/applications/CoSimulationApplication && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gabriela/Software/Kratos/applications/CoSimulationApplication/co_simulation_application.cpp > CMakeFiles/KratosCoSimulationApplication.dir/co_simulation_application.cpp.i

applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/co_simulation_application.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KratosCoSimulationApplication.dir/co_simulation_application.cpp.s"
	cd /home/gabriela/Software/Kratos/cmake_build/applications/CoSimulationApplication && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gabriela/Software/Kratos/applications/CoSimulationApplication/co_simulation_application.cpp -o CMakeFiles/KratosCoSimulationApplication.dir/co_simulation_application.cpp.s

applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/co_simulation_application.cpp.o.requires:

.PHONY : applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/co_simulation_application.cpp.o.requires

applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/co_simulation_application.cpp.o.provides: applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/co_simulation_application.cpp.o.requires
	$(MAKE) -f applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/build.make applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/co_simulation_application.cpp.o.provides.build
.PHONY : applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/co_simulation_application.cpp.o.provides

applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/co_simulation_application.cpp.o.provides.build: applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/co_simulation_application.cpp.o


applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/custom_python/co_simulation_python_application.cpp.o: applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/flags.make
applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/custom_python/co_simulation_python_application.cpp.o: ../applications/CoSimulationApplication/custom_python/co_simulation_python_application.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gabriela/Software/Kratos/cmake_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/custom_python/co_simulation_python_application.cpp.o"
	cd /home/gabriela/Software/Kratos/cmake_build/applications/CoSimulationApplication && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/KratosCoSimulationApplication.dir/custom_python/co_simulation_python_application.cpp.o -c /home/gabriela/Software/Kratos/applications/CoSimulationApplication/custom_python/co_simulation_python_application.cpp

applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/custom_python/co_simulation_python_application.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KratosCoSimulationApplication.dir/custom_python/co_simulation_python_application.cpp.i"
	cd /home/gabriela/Software/Kratos/cmake_build/applications/CoSimulationApplication && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gabriela/Software/Kratos/applications/CoSimulationApplication/custom_python/co_simulation_python_application.cpp > CMakeFiles/KratosCoSimulationApplication.dir/custom_python/co_simulation_python_application.cpp.i

applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/custom_python/co_simulation_python_application.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KratosCoSimulationApplication.dir/custom_python/co_simulation_python_application.cpp.s"
	cd /home/gabriela/Software/Kratos/cmake_build/applications/CoSimulationApplication && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gabriela/Software/Kratos/applications/CoSimulationApplication/custom_python/co_simulation_python_application.cpp -o CMakeFiles/KratosCoSimulationApplication.dir/custom_python/co_simulation_python_application.cpp.s

applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/custom_python/co_simulation_python_application.cpp.o.requires:

.PHONY : applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/custom_python/co_simulation_python_application.cpp.o.requires

applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/custom_python/co_simulation_python_application.cpp.o.provides: applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/custom_python/co_simulation_python_application.cpp.o.requires
	$(MAKE) -f applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/build.make applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/custom_python/co_simulation_python_application.cpp.o.provides.build
.PHONY : applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/custom_python/co_simulation_python_application.cpp.o.provides

applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/custom_python/co_simulation_python_application.cpp.o.provides.build: applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/custom_python/co_simulation_python_application.cpp.o


applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/custom_python/add_custom_io_to_python.cpp.o: applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/flags.make
applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/custom_python/add_custom_io_to_python.cpp.o: ../applications/CoSimulationApplication/custom_python/add_custom_io_to_python.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gabriela/Software/Kratos/cmake_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/custom_python/add_custom_io_to_python.cpp.o"
	cd /home/gabriela/Software/Kratos/cmake_build/applications/CoSimulationApplication && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/KratosCoSimulationApplication.dir/custom_python/add_custom_io_to_python.cpp.o -c /home/gabriela/Software/Kratos/applications/CoSimulationApplication/custom_python/add_custom_io_to_python.cpp

applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/custom_python/add_custom_io_to_python.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KratosCoSimulationApplication.dir/custom_python/add_custom_io_to_python.cpp.i"
	cd /home/gabriela/Software/Kratos/cmake_build/applications/CoSimulationApplication && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gabriela/Software/Kratos/applications/CoSimulationApplication/custom_python/add_custom_io_to_python.cpp > CMakeFiles/KratosCoSimulationApplication.dir/custom_python/add_custom_io_to_python.cpp.i

applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/custom_python/add_custom_io_to_python.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KratosCoSimulationApplication.dir/custom_python/add_custom_io_to_python.cpp.s"
	cd /home/gabriela/Software/Kratos/cmake_build/applications/CoSimulationApplication && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gabriela/Software/Kratos/applications/CoSimulationApplication/custom_python/add_custom_io_to_python.cpp -o CMakeFiles/KratosCoSimulationApplication.dir/custom_python/add_custom_io_to_python.cpp.s

applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/custom_python/add_custom_io_to_python.cpp.o.requires:

.PHONY : applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/custom_python/add_custom_io_to_python.cpp.o.requires

applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/custom_python/add_custom_io_to_python.cpp.o.provides: applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/custom_python/add_custom_io_to_python.cpp.o.requires
	$(MAKE) -f applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/build.make applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/custom_python/add_custom_io_to_python.cpp.o.provides.build
.PHONY : applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/custom_python/add_custom_io_to_python.cpp.o.provides

applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/custom_python/add_custom_io_to_python.cpp.o.provides.build: applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/custom_python/add_custom_io_to_python.cpp.o


applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/tests/cpp_tests/test_multiple_includes_api_headers.cpp.o: applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/flags.make
applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/tests/cpp_tests/test_multiple_includes_api_headers.cpp.o: ../applications/CoSimulationApplication/tests/cpp_tests/test_multiple_includes_api_headers.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gabriela/Software/Kratos/cmake_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/tests/cpp_tests/test_multiple_includes_api_headers.cpp.o"
	cd /home/gabriela/Software/Kratos/cmake_build/applications/CoSimulationApplication && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/KratosCoSimulationApplication.dir/tests/cpp_tests/test_multiple_includes_api_headers.cpp.o -c /home/gabriela/Software/Kratos/applications/CoSimulationApplication/tests/cpp_tests/test_multiple_includes_api_headers.cpp

applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/tests/cpp_tests/test_multiple_includes_api_headers.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KratosCoSimulationApplication.dir/tests/cpp_tests/test_multiple_includes_api_headers.cpp.i"
	cd /home/gabriela/Software/Kratos/cmake_build/applications/CoSimulationApplication && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gabriela/Software/Kratos/applications/CoSimulationApplication/tests/cpp_tests/test_multiple_includes_api_headers.cpp > CMakeFiles/KratosCoSimulationApplication.dir/tests/cpp_tests/test_multiple_includes_api_headers.cpp.i

applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/tests/cpp_tests/test_multiple_includes_api_headers.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KratosCoSimulationApplication.dir/tests/cpp_tests/test_multiple_includes_api_headers.cpp.s"
	cd /home/gabriela/Software/Kratos/cmake_build/applications/CoSimulationApplication && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gabriela/Software/Kratos/applications/CoSimulationApplication/tests/cpp_tests/test_multiple_includes_api_headers.cpp -o CMakeFiles/KratosCoSimulationApplication.dir/tests/cpp_tests/test_multiple_includes_api_headers.cpp.s

applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/tests/cpp_tests/test_multiple_includes_api_headers.cpp.o.requires:

.PHONY : applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/tests/cpp_tests/test_multiple_includes_api_headers.cpp.o.requires

applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/tests/cpp_tests/test_multiple_includes_api_headers.cpp.o.provides: applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/tests/cpp_tests/test_multiple_includes_api_headers.cpp.o.requires
	$(MAKE) -f applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/build.make applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/tests/cpp_tests/test_multiple_includes_api_headers.cpp.o.provides.build
.PHONY : applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/tests/cpp_tests/test_multiple_includes_api_headers.cpp.o.provides

applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/tests/cpp_tests/test_multiple_includes_api_headers.cpp.o.provides.build: applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/tests/cpp_tests/test_multiple_includes_api_headers.cpp.o


# Object files for target KratosCoSimulationApplication
KratosCoSimulationApplication_OBJECTS = \
"CMakeFiles/KratosCoSimulationApplication.dir/co_simulation_application.cpp.o" \
"CMakeFiles/KratosCoSimulationApplication.dir/custom_python/co_simulation_python_application.cpp.o" \
"CMakeFiles/KratosCoSimulationApplication.dir/custom_python/add_custom_io_to_python.cpp.o" \
"CMakeFiles/KratosCoSimulationApplication.dir/tests/cpp_tests/test_multiple_includes_api_headers.cpp.o"

# External object files for target KratosCoSimulationApplication
KratosCoSimulationApplication_EXTERNAL_OBJECTS =

applications/CoSimulationApplication/KratosCoSimulationApplication.cpython-36m-x86_64-linux-gnu.so: applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/co_simulation_application.cpp.o
applications/CoSimulationApplication/KratosCoSimulationApplication.cpython-36m-x86_64-linux-gnu.so: applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/custom_python/co_simulation_python_application.cpp.o
applications/CoSimulationApplication/KratosCoSimulationApplication.cpython-36m-x86_64-linux-gnu.so: applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/custom_python/add_custom_io_to_python.cpp.o
applications/CoSimulationApplication/KratosCoSimulationApplication.cpython-36m-x86_64-linux-gnu.so: applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/tests/cpp_tests/test_multiple_includes_api_headers.cpp.o
applications/CoSimulationApplication/KratosCoSimulationApplication.cpython-36m-x86_64-linux-gnu.so: applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/build.make
applications/CoSimulationApplication/KratosCoSimulationApplication.cpython-36m-x86_64-linux-gnu.so: kratos/libKratosCore.so
applications/CoSimulationApplication/KratosCoSimulationApplication.cpython-36m-x86_64-linux-gnu.so: external_libraries/gidpost/libgidpost.a
applications/CoSimulationApplication/KratosCoSimulationApplication.cpython-36m-x86_64-linux-gnu.so: /usr/lib/x86_64-linux-gnu/libz.so
applications/CoSimulationApplication/KratosCoSimulationApplication.cpython-36m-x86_64-linux-gnu.so: applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gabriela/Software/Kratos/cmake_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX shared module KratosCoSimulationApplication.cpython-36m-x86_64-linux-gnu.so"
	cd /home/gabriela/Software/Kratos/cmake_build/applications/CoSimulationApplication && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/KratosCoSimulationApplication.dir/link.txt --verbose=$(VERBOSE)
	cd /home/gabriela/Software/Kratos/cmake_build/applications/CoSimulationApplication && /usr/bin/strip /home/gabriela/Software/Kratos/cmake_build/applications/CoSimulationApplication/KratosCoSimulationApplication.cpython-36m-x86_64-linux-gnu.so

# Rule to build all files generated by this target.
applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/build: applications/CoSimulationApplication/KratosCoSimulationApplication.cpython-36m-x86_64-linux-gnu.so

.PHONY : applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/build

applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/requires: applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/co_simulation_application.cpp.o.requires
applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/requires: applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/custom_python/co_simulation_python_application.cpp.o.requires
applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/requires: applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/custom_python/add_custom_io_to_python.cpp.o.requires
applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/requires: applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/tests/cpp_tests/test_multiple_includes_api_headers.cpp.o.requires

.PHONY : applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/requires

applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/clean:
	cd /home/gabriela/Software/Kratos/cmake_build/applications/CoSimulationApplication && $(CMAKE_COMMAND) -P CMakeFiles/KratosCoSimulationApplication.dir/cmake_clean.cmake
.PHONY : applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/clean

applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/depend:
	cd /home/gabriela/Software/Kratos/cmake_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gabriela/Software/Kratos /home/gabriela/Software/Kratos/applications/CoSimulationApplication /home/gabriela/Software/Kratos/cmake_build /home/gabriela/Software/Kratos/cmake_build/applications/CoSimulationApplication /home/gabriela/Software/Kratos/cmake_build/applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : applications/CoSimulationApplication/CMakeFiles/KratosCoSimulationApplication.dir/depend
