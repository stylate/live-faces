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
include CMakeFiles/kvs_producer_plugin_demo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/kvs_producer_plugin_demo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/kvs_producer_plugin_demo.dir/flags.make

CMakeFiles/kvs_producer_plugin_demo.dir/demo-src/kvs_producer_plugin_demo.cpp.o: CMakeFiles/kvs_producer_plugin_demo.dir/flags.make
CMakeFiles/kvs_producer_plugin_demo.dir/demo-src/kvs_producer_plugin_demo.cpp.o: demo-src/kvs_producer_plugin_demo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alanng/work/cpp/kinesis-video-gstreamer-plugin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/kvs_producer_plugin_demo.dir/demo-src/kvs_producer_plugin_demo.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/kvs_producer_plugin_demo.dir/demo-src/kvs_producer_plugin_demo.cpp.o -c /Users/alanng/work/cpp/kinesis-video-gstreamer-plugin/demo-src/kvs_producer_plugin_demo.cpp

CMakeFiles/kvs_producer_plugin_demo.dir/demo-src/kvs_producer_plugin_demo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kvs_producer_plugin_demo.dir/demo-src/kvs_producer_plugin_demo.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alanng/work/cpp/kinesis-video-gstreamer-plugin/demo-src/kvs_producer_plugin_demo.cpp > CMakeFiles/kvs_producer_plugin_demo.dir/demo-src/kvs_producer_plugin_demo.cpp.i

CMakeFiles/kvs_producer_plugin_demo.dir/demo-src/kvs_producer_plugin_demo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kvs_producer_plugin_demo.dir/demo-src/kvs_producer_plugin_demo.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alanng/work/cpp/kinesis-video-gstreamer-plugin/demo-src/kvs_producer_plugin_demo.cpp -o CMakeFiles/kvs_producer_plugin_demo.dir/demo-src/kvs_producer_plugin_demo.cpp.s

# Object files for target kvs_producer_plugin_demo
kvs_producer_plugin_demo_OBJECTS = \
"CMakeFiles/kvs_producer_plugin_demo.dir/demo-src/kvs_producer_plugin_demo.cpp.o"

# External object files for target kvs_producer_plugin_demo
kvs_producer_plugin_demo_EXTERNAL_OBJECTS =

kvs_producer_plugin_demo: CMakeFiles/kvs_producer_plugin_demo.dir/demo-src/kvs_producer_plugin_demo.cpp.o
kvs_producer_plugin_demo: CMakeFiles/kvs_producer_plugin_demo.dir/build.make
kvs_producer_plugin_demo: CMakeFiles/kvs_producer_plugin_demo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/alanng/work/cpp/kinesis-video-gstreamer-plugin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable kvs_producer_plugin_demo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/kvs_producer_plugin_demo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/kvs_producer_plugin_demo.dir/build: kvs_producer_plugin_demo

.PHONY : CMakeFiles/kvs_producer_plugin_demo.dir/build

CMakeFiles/kvs_producer_plugin_demo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/kvs_producer_plugin_demo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/kvs_producer_plugin_demo.dir/clean

CMakeFiles/kvs_producer_plugin_demo.dir/depend:
	cd /Users/alanng/work/cpp/kinesis-video-gstreamer-plugin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/alanng/work/cpp/kinesis-video-gstreamer-plugin /Users/alanng/work/cpp/kinesis-video-gstreamer-plugin /Users/alanng/work/cpp/kinesis-video-gstreamer-plugin /Users/alanng/work/cpp/kinesis-video-gstreamer-plugin /Users/alanng/work/cpp/kinesis-video-gstreamer-plugin/CMakeFiles/kvs_producer_plugin_demo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/kvs_producer_plugin_demo.dir/depend

