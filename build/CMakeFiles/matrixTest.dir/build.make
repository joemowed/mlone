# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_SOURCE_DIR = /home/jmaloney/Documents/mlone

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jmaloney/Documents/mlone/build

# Include any dependencies generated for this target.
include CMakeFiles/matrixTest.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/matrixTest.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/matrixTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/matrixTest.dir/flags.make

CMakeFiles/matrixTest.dir/src/testing/matrixTest.cc.o: CMakeFiles/matrixTest.dir/flags.make
CMakeFiles/matrixTest.dir/src/testing/matrixTest.cc.o: /home/jmaloney/Documents/mlone/src/testing/matrixTest.cc
CMakeFiles/matrixTest.dir/src/testing/matrixTest.cc.o: CMakeFiles/matrixTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/jmaloney/Documents/mlone/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/matrixTest.dir/src/testing/matrixTest.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/matrixTest.dir/src/testing/matrixTest.cc.o -MF CMakeFiles/matrixTest.dir/src/testing/matrixTest.cc.o.d -o CMakeFiles/matrixTest.dir/src/testing/matrixTest.cc.o -c /home/jmaloney/Documents/mlone/src/testing/matrixTest.cc

CMakeFiles/matrixTest.dir/src/testing/matrixTest.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/matrixTest.dir/src/testing/matrixTest.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jmaloney/Documents/mlone/src/testing/matrixTest.cc > CMakeFiles/matrixTest.dir/src/testing/matrixTest.cc.i

CMakeFiles/matrixTest.dir/src/testing/matrixTest.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/matrixTest.dir/src/testing/matrixTest.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jmaloney/Documents/mlone/src/testing/matrixTest.cc -o CMakeFiles/matrixTest.dir/src/testing/matrixTest.cc.s

# Object files for target matrixTest
matrixTest_OBJECTS = \
"CMakeFiles/matrixTest.dir/src/testing/matrixTest.cc.o"

# External object files for target matrixTest
matrixTest_EXTERNAL_OBJECTS =

matrixTest: CMakeFiles/matrixTest.dir/src/testing/matrixTest.cc.o
matrixTest: CMakeFiles/matrixTest.dir/build.make
matrixTest: lib/libgtest_main.a
matrixTest: lib/libgtest.a
matrixTest: CMakeFiles/matrixTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/jmaloney/Documents/mlone/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable matrixTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/matrixTest.dir/link.txt --verbose=$(VERBOSE)
	/usr/bin/cmake -D TEST_TARGET=matrixTest -D TEST_EXECUTABLE=/home/jmaloney/Documents/mlone/build/matrixTest -D TEST_EXECUTOR= -D TEST_WORKING_DIR=/home/jmaloney/Documents/mlone/build -D TEST_EXTRA_ARGS= -D TEST_PROPERTIES= -D TEST_PREFIX= -D TEST_SUFFIX= -D TEST_FILTER= -D NO_PRETTY_TYPES=FALSE -D NO_PRETTY_VALUES=FALSE -D TEST_LIST=matrixTest_TESTS -D CTEST_FILE=/home/jmaloney/Documents/mlone/build/matrixTest[1]_tests.cmake -D TEST_DISCOVERY_TIMEOUT=5 -D TEST_XML_OUTPUT_DIR= -P /usr/share/cmake-3.27/Modules/GoogleTestAddTests.cmake

# Rule to build all files generated by this target.
CMakeFiles/matrixTest.dir/build: matrixTest
.PHONY : CMakeFiles/matrixTest.dir/build

CMakeFiles/matrixTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/matrixTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/matrixTest.dir/clean

CMakeFiles/matrixTest.dir/depend:
	cd /home/jmaloney/Documents/mlone/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jmaloney/Documents/mlone /home/jmaloney/Documents/mlone /home/jmaloney/Documents/mlone/build /home/jmaloney/Documents/mlone/build /home/jmaloney/Documents/mlone/build/CMakeFiles/matrixTest.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/matrixTest.dir/depend

