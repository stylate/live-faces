# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.11

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.11.4/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.11.4/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/alanng/work/cpp/kinesis-video-gstreamer-plugin

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/alanng/work/cpp/kinesis-video-gstreamer-plugin

# Include any dependencies generated for this target.
include CMakeFiles/gstkvsplugintest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/gstkvsplugintest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gstkvsplugintest.dir/flags.make

CMakeFiles/gstkvsplugintest.dir/plugin-src/gstkvstest.cpp.o: CMakeFiles/gstkvsplugintest.dir/flags.make
CMakeFiles/gstkvsplugintest.dir/plugin-src/gstkvstest.cpp.o: plugin-src/gstkvstest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alanng/work/cpp/kinesis-video-gstreamer-plugin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/gstkvsplugintest.dir/plugin-src/gstkvstest.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gstkvsplugintest.dir/plugin-src/gstkvstest.cpp.o -c /Users/alanng/work/cpp/kinesis-video-gstreamer-plugin/plugin-src/gstkvstest.cpp

CMakeFiles/gstkvsplugintest.dir/plugin-src/gstkvstest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gstkvsplugintest.dir/plugin-src/gstkvstest.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alanng/work/cpp/kinesis-video-gstreamer-plugin/plugin-src/gstkvstest.cpp > CMakeFiles/gstkvsplugintest.dir/plugin-src/gstkvstest.cpp.i

CMakeFiles/gstkvsplugintest.dir/plugin-src/gstkvstest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gstkvsplugintest.dir/plugin-src/gstkvstest.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alanng/work/cpp/kinesis-video-gstreamer-plugin/plugin-src/gstkvstest.cpp -o CMakeFiles/gstkvsplugintest.dir/plugin-src/gstkvstest.cpp.s

# Object files for target gstkvsplugintest
gstkvsplugintest_OBJECTS = \
"CMakeFiles/gstkvsplugintest.dir/plugin-src/gstkvstest.cpp.o"

# External object files for target gstkvsplugintest
gstkvsplugintest_EXTERNAL_OBJECTS =

gstkvsplugintest: CMakeFiles/gstkvsplugintest.dir/plugin-src/gstkvstest.cpp.o
gstkvsplugintest: CMakeFiles/gstkvsplugintest.dir/build.make
gstkvsplugintest: CMakeFiles/gstkvsplugintest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/alanng/work/cpp/kinesis-video-gstreamer-plugin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable gstkvsplugintest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gstkvsplugintest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gstkvsplugintest.dir/build: gstkvsplugintest

.PHONY : CMakeFiles/gstkvsplugintest.dir/build

CMakeFiles/gstkvsplugintest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gstkvsplugintest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gstkvsplugintest.dir/clean

CMakeFiles/gstkvsplugintest.dir/depend:
	cd /Users/alanng/work/cpp/kinesis-video-gstreamer-plugin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/alanng/work/cpp/kinesis-video-gstreamer-plugin /Users/alanng/work/cpp/kinesis-video-gstreamer-plugin /Users/alanng/work/cpp/kinesis-video-gstreamer-plugin /Users/alanng/work/cpp/kinesis-video-gstreamer-plugin /Users/alanng/work/cpp/kinesis-video-gstreamer-plugin/CMakeFiles/gstkvsplugintest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/gstkvsplugintest.dir/depend

