# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.24.2/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.24.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/tanyong/Desktop/code/demo/googletest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/tanyong/Desktop/code/demo/googletest/build

# Include any dependencies generated for this target.
include CMakeFiles/MyTests.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MyTests.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MyTests.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MyTests.dir/flags.make

CMakeFiles/MyTests.dir/test.cpp.o: CMakeFiles/MyTests.dir/flags.make
CMakeFiles/MyTests.dir/test.cpp.o: /Users/tanyong/Desktop/code/demo/googletest/test.cpp
CMakeFiles/MyTests.dir/test.cpp.o: CMakeFiles/MyTests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/tanyong/Desktop/code/demo/googletest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MyTests.dir/test.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyTests.dir/test.cpp.o -MF CMakeFiles/MyTests.dir/test.cpp.o.d -o CMakeFiles/MyTests.dir/test.cpp.o -c /Users/tanyong/Desktop/code/demo/googletest/test.cpp

CMakeFiles/MyTests.dir/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyTests.dir/test.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/tanyong/Desktop/code/demo/googletest/test.cpp > CMakeFiles/MyTests.dir/test.cpp.i

CMakeFiles/MyTests.dir/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyTests.dir/test.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/tanyong/Desktop/code/demo/googletest/test.cpp -o CMakeFiles/MyTests.dir/test.cpp.s

# Object files for target MyTests
MyTests_OBJECTS = \
"CMakeFiles/MyTests.dir/test.cpp.o"

# External object files for target MyTests
MyTests_EXTERNAL_OBJECTS =

MyTests: CMakeFiles/MyTests.dir/test.cpp.o
MyTests: CMakeFiles/MyTests.dir/build.make
MyTests: /usr/local/lib/libgtest.a
MyTests: /usr/local/lib/libgtest_main.a
MyTests: /usr/local/lib/libgtest.a
MyTests: CMakeFiles/MyTests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/tanyong/Desktop/code/demo/googletest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable MyTests"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MyTests.dir/link.txt --verbose=$(VERBOSE)
	/opt/homebrew/Cellar/cmake/3.24.2/bin/cmake -D TEST_TARGET=MyTests -D TEST_EXECUTABLE=/Users/tanyong/Desktop/code/demo/googletest/build/MyTests -D TEST_EXECUTOR= -D TEST_WORKING_DIR=/Users/tanyong/Desktop/code/demo/googletest/build -D TEST_EXTRA_ARGS= -D TEST_PROPERTIES= -D TEST_PREFIX= -D TEST_SUFFIX= -D TEST_FILTER= -D NO_PRETTY_TYPES=FALSE -D NO_PRETTY_VALUES=FALSE -D TEST_LIST=MyTests_TESTS -D CTEST_FILE=/Users/tanyong/Desktop/code/demo/googletest/build/MyTests[1]_tests.cmake -D TEST_DISCOVERY_TIMEOUT=5 -D TEST_XML_OUTPUT_DIR= -P /opt/homebrew/Cellar/cmake/3.24.2/share/cmake/Modules/GoogleTestAddTests.cmake

# Rule to build all files generated by this target.
CMakeFiles/MyTests.dir/build: MyTests
.PHONY : CMakeFiles/MyTests.dir/build

CMakeFiles/MyTests.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MyTests.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MyTests.dir/clean

CMakeFiles/MyTests.dir/depend:
	cd /Users/tanyong/Desktop/code/demo/googletest/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/tanyong/Desktop/code/demo/googletest /Users/tanyong/Desktop/code/demo/googletest /Users/tanyong/Desktop/code/demo/googletest/build /Users/tanyong/Desktop/code/demo/googletest/build /Users/tanyong/Desktop/code/demo/googletest/build/CMakeFiles/MyTests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MyTests.dir/depend

