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
CMAKE_SOURCE_DIR = /Users/alanng/work/cpp/kinesis-video-native-build

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/alanng/work/cpp/kinesis-video-native-build

# Include any dependencies generated for this target.
include CMakeFiles/kinesis_video_gstreamer_sample_app.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/kinesis_video_gstreamer_sample_app.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/kinesis_video_gstreamer_sample_app.dir/flags.make

CMakeFiles/kinesis_video_gstreamer_sample_app.dir/Users/alanng/work/cpp/kinesis-video-gst-demo/kinesis_video_gstreamer_sample_app.cpp.o: CMakeFiles/kinesis_video_gstreamer_sample_app.dir/flags.make
CMakeFiles/kinesis_video_gstreamer_sample_app.dir/Users/alanng/work/cpp/kinesis-video-gst-demo/kinesis_video_gstreamer_sample_app.cpp.o: /Users/alanng/work/cpp/kinesis-video-gst-demo/kinesis_video_gstreamer_sample_app.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alanng/work/cpp/kinesis-video-native-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/kinesis_video_gstreamer_sample_app.dir/Users/alanng/work/cpp/kinesis-video-gst-demo/kinesis_video_gstreamer_sample_app.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/kinesis_video_gstreamer_sample_app.dir/Users/alanng/work/cpp/kinesis-video-gst-demo/kinesis_video_gstreamer_sample_app.cpp.o -c /Users/alanng/work/cpp/kinesis-video-gst-demo/kinesis_video_gstreamer_sample_app.cpp

CMakeFiles/kinesis_video_gstreamer_sample_app.dir/Users/alanng/work/cpp/kinesis-video-gst-demo/kinesis_video_gstreamer_sample_app.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kinesis_video_gstreamer_sample_app.dir/Users/alanng/work/cpp/kinesis-video-gst-demo/kinesis_video_gstreamer_sample_app.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alanng/work/cpp/kinesis-video-gst-demo/kinesis_video_gstreamer_sample_app.cpp > CMakeFiles/kinesis_video_gstreamer_sample_app.dir/Users/alanng/work/cpp/kinesis-video-gst-demo/kinesis_video_gstreamer_sample_app.cpp.i

CMakeFiles/kinesis_video_gstreamer_sample_app.dir/Users/alanng/work/cpp/kinesis-video-gst-demo/kinesis_video_gstreamer_sample_app.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kinesis_video_gstreamer_sample_app.dir/Users/alanng/work/cpp/kinesis-video-gst-demo/kinesis_video_gstreamer_sample_app.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alanng/work/cpp/kinesis-video-gst-demo/kinesis_video_gstreamer_sample_app.cpp -o CMakeFiles/kinesis_video_gstreamer_sample_app.dir/Users/alanng/work/cpp/kinesis-video-gst-demo/kinesis_video_gstreamer_sample_app.cpp.s

# Object files for target kinesis_video_gstreamer_sample_app
kinesis_video_gstreamer_sample_app_OBJECTS = \
"CMakeFiles/kinesis_video_gstreamer_sample_app.dir/Users/alanng/work/cpp/kinesis-video-gst-demo/kinesis_video_gstreamer_sample_app.cpp.o"

# External object files for target kinesis_video_gstreamer_sample_app
kinesis_video_gstreamer_sample_app_EXTERNAL_OBJECTS =

kinesis_video_gstreamer_sample_app: CMakeFiles/kinesis_video_gstreamer_sample_app.dir/Users/alanng/work/cpp/kinesis-video-gst-demo/kinesis_video_gstreamer_sample_app.cpp.o
kinesis_video_gstreamer_sample_app: CMakeFiles/kinesis_video_gstreamer_sample_app.dir/build.make
kinesis_video_gstreamer_sample_app: libproducer.dylib
kinesis_video_gstreamer_sample_app: downloads/local/lib/libgtest_main.dylib
kinesis_video_gstreamer_sample_app: downloads/local/lib/libgtest.dylib
kinesis_video_gstreamer_sample_app: CMakeFiles/kinesis_video_gstreamer_sample_app.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/alanng/work/cpp/kinesis-video-native-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable kinesis_video_gstreamer_sample_app"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/kinesis_video_gstreamer_sample_app.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/kinesis_video_gstreamer_sample_app.dir/build: kinesis_video_gstreamer_sample_app

.PHONY : CMakeFiles/kinesis_video_gstreamer_sample_app.dir/build

CMakeFiles/kinesis_video_gstreamer_sample_app.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/kinesis_video_gstreamer_sample_app.dir/cmake_clean.cmake
.PHONY : CMakeFiles/kinesis_video_gstreamer_sample_app.dir/clean

CMakeFiles/kinesis_video_gstreamer_sample_app.dir/depend:
	cd /Users/alanng/work/cpp/kinesis-video-native-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/alanng/work/cpp/kinesis-video-native-build /Users/alanng/work/cpp/kinesis-video-native-build /Users/alanng/work/cpp/kinesis-video-native-build /Users/alanng/work/cpp/kinesis-video-native-build /Users/alanng/work/cpp/kinesis-video-native-build/CMakeFiles/kinesis_video_gstreamer_sample_app.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/kinesis_video_gstreamer_sample_app.dir/depend
