# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/amanuel/Desktop/devs/cpp-tknizer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/amanuel/Desktop/devs/cpp-tknizer/build

# Include any dependencies generated for this target.
include CMakeFiles/tknizer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/tknizer.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/tknizer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tknizer.dir/flags.make

CMakeFiles/tknizer.dir/main.cpp.o: CMakeFiles/tknizer.dir/flags.make
CMakeFiles/tknizer.dir/main.cpp.o: /Users/amanuel/Desktop/devs/cpp-tknizer/main.cpp
CMakeFiles/tknizer.dir/main.cpp.o: CMakeFiles/tknizer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/amanuel/Desktop/devs/cpp-tknizer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tknizer.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/tknizer.dir/main.cpp.o -MF CMakeFiles/tknizer.dir/main.cpp.o.d -o CMakeFiles/tknizer.dir/main.cpp.o -c /Users/amanuel/Desktop/devs/cpp-tknizer/main.cpp

CMakeFiles/tknizer.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/tknizer.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/amanuel/Desktop/devs/cpp-tknizer/main.cpp > CMakeFiles/tknizer.dir/main.cpp.i

CMakeFiles/tknizer.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/tknizer.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/amanuel/Desktop/devs/cpp-tknizer/main.cpp -o CMakeFiles/tknizer.dir/main.cpp.s

# Object files for target tknizer
tknizer_OBJECTS = \
"CMakeFiles/tknizer.dir/main.cpp.o"

# External object files for target tknizer
tknizer_EXTERNAL_OBJECTS =

tknizer: CMakeFiles/tknizer.dir/main.cpp.o
tknizer: CMakeFiles/tknizer.dir/build.make
tknizer: tokenizers-cpp/libtokenizers_cpp.a
tknizer: tokenizers-cpp/aarch64-apple-darwin/release/libtokenizers_c.a
tknizer: tokenizers-cpp/sentencepiece/src/libsentencepiece.a
tknizer: CMakeFiles/tknizer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/amanuel/Desktop/devs/cpp-tknizer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable tknizer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tknizer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tknizer.dir/build: tknizer
.PHONY : CMakeFiles/tknizer.dir/build

CMakeFiles/tknizer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tknizer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tknizer.dir/clean

CMakeFiles/tknizer.dir/depend:
	cd /Users/amanuel/Desktop/devs/cpp-tknizer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/amanuel/Desktop/devs/cpp-tknizer /Users/amanuel/Desktop/devs/cpp-tknizer /Users/amanuel/Desktop/devs/cpp-tknizer/build /Users/amanuel/Desktop/devs/cpp-tknizer/build /Users/amanuel/Desktop/devs/cpp-tknizer/build/CMakeFiles/tknizer.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/tknizer.dir/depend
