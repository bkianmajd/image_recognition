# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/babak/Desktop/open_cv/opencv-3.4.1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/babak/Desktop/open_cv/opencv-3.4.1/build

# Utility rule file for pch_Generate_opencv_test_videoio.

# Include the progress variables for this target.
include modules/videoio/CMakeFiles/pch_Generate_opencv_test_videoio.dir/progress.make

modules/videoio/CMakeFiles/pch_Generate_opencv_test_videoio: modules/videoio/test_precomp.hpp.gch/opencv_test_videoio_Release.gch


modules/videoio/test_precomp.hpp.gch/opencv_test_videoio_Release.gch: ../modules/videoio/test/test_precomp.hpp
modules/videoio/test_precomp.hpp.gch/opencv_test_videoio_Release.gch: modules/videoio/test_precomp.hpp
modules/videoio/test_precomp.hpp.gch/opencv_test_videoio_Release.gch: lib/libopencv_test_videoio_pch_dephelp.a
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/babak/Desktop/open_cv/opencv-3.4.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating test_precomp.hpp.gch/opencv_test_videoio_Release.gch"
	cd /home/babak/Desktop/open_cv/opencv-3.4.1/build/modules/videoio && /usr/bin/cmake -E make_directory /home/babak/Desktop/open_cv/opencv-3.4.1/build/modules/videoio/test_precomp.hpp.gch
	cd /home/babak/Desktop/open_cv/opencv-3.4.1/build/modules/videoio && /usr/bin/c++ -O3 -DNDEBUG -DNDEBUG "-D__OPENCV_BUILD=1" "-D_USE_MATH_DEFINES" "-D__STDC_CONSTANT_MACROS" "-D__STDC_LIMIT_MACROS" "-D__STDC_FORMAT_MACROS" "-D__OPENCV_TESTS=1" -I"/home/babak/Desktop/open_cv/opencv-3.4.1/build/3rdparty/ippicv/ippicv_lnx/include" -I"/home/babak/Desktop/open_cv/opencv-3.4.1/build/3rdparty/ippicv/ippiw_lnx/include" -I"/home/babak/Desktop/open_cv/opencv-3.4.1/build" -I"/home/babak/Desktop/open_cv/opencv-3.4.1/build/3rdparty/ippicv/ippicv_lnx/include" -I"/home/babak/Desktop/open_cv/opencv-3.4.1/build/3rdparty/ippicv/ippiw_lnx/include" -I"/home/babak/Desktop/open_cv/opencv-3.4.1/build" -I"/home/babak/Desktop/open_cv/opencv-3.4.1/modules/ts/include" -I"/home/babak/Desktop/open_cv/opencv-3.4.1/modules/videoio/include" -I"/home/babak/Desktop/open_cv/opencv-3.4.1/modules/imgcodecs/include" -I"/home/babak/Desktop/open_cv/opencv-3.4.1/modules/videoio/include" -I"/home/babak/Desktop/open_cv/opencv-3.4.1/modules/core/include" -I"/home/babak/Desktop/open_cv/opencv-3.4.1/modules/imgproc/include" -I"/home/babak/Desktop/open_cv/opencv-3.4.1/modules/imgcodecs/include" -I"/home/babak/Desktop/open_cv/opencv-3.4.1/modules/core/include" -I"/home/babak/Desktop/open_cv/opencv-3.4.1/modules/imgproc/include" -I"/home/babak/Desktop/open_cv/opencv-3.4.1/modules/imgcodecs/include" -I"/home/babak/Desktop/open_cv/opencv-3.4.1/modules/videoio/include" -I"/home/babak/Desktop/open_cv/opencv-3.4.1/modules/highgui/include" -I"/home/babak/Desktop/open_cv/opencv-3.4.1/modules/videoio/test" -fsigned-char -W -Wall -Werror=return-type -Werror=non-virtual-dtor -Werror=address -Werror=sequence-point -Wformat -Werror=format-security -Wmissing-declarations -Wundef -Winit-self -Wpointer-arith -Wshadow -Wsign-promo -Wuninitialized -Winit-self -Wno-narrowing -Wno-delete-non-virtual-dtor -Wno-comment -fdiagnostics-show-option -Wno-long-long -pthread -fomit-frame-pointer -ffunction-sections -fdata-sections -msse -msse2 -msse3 -fvisibility=hidden -fvisibility-inlines-hidden -Wno-deprecated-declarations -fPIE -x c++-header -o /home/babak/Desktop/open_cv/opencv-3.4.1/build/modules/videoio/test_precomp.hpp.gch/opencv_test_videoio_Release.gch /home/babak/Desktop/open_cv/opencv-3.4.1/build/modules/videoio/test_precomp.hpp

modules/videoio/test_precomp.hpp: ../modules/videoio/test/test_precomp.hpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/babak/Desktop/open_cv/opencv-3.4.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating test_precomp.hpp"
	cd /home/babak/Desktop/open_cv/opencv-3.4.1/build/modules/videoio && /usr/bin/cmake -E copy_if_different /home/babak/Desktop/open_cv/opencv-3.4.1/modules/videoio/test/test_precomp.hpp /home/babak/Desktop/open_cv/opencv-3.4.1/build/modules/videoio/test_precomp.hpp

pch_Generate_opencv_test_videoio: modules/videoio/CMakeFiles/pch_Generate_opencv_test_videoio
pch_Generate_opencv_test_videoio: modules/videoio/test_precomp.hpp.gch/opencv_test_videoio_Release.gch
pch_Generate_opencv_test_videoio: modules/videoio/test_precomp.hpp
pch_Generate_opencv_test_videoio: modules/videoio/CMakeFiles/pch_Generate_opencv_test_videoio.dir/build.make

.PHONY : pch_Generate_opencv_test_videoio

# Rule to build all files generated by this target.
modules/videoio/CMakeFiles/pch_Generate_opencv_test_videoio.dir/build: pch_Generate_opencv_test_videoio

.PHONY : modules/videoio/CMakeFiles/pch_Generate_opencv_test_videoio.dir/build

modules/videoio/CMakeFiles/pch_Generate_opencv_test_videoio.dir/clean:
	cd /home/babak/Desktop/open_cv/opencv-3.4.1/build/modules/videoio && $(CMAKE_COMMAND) -P CMakeFiles/pch_Generate_opencv_test_videoio.dir/cmake_clean.cmake
.PHONY : modules/videoio/CMakeFiles/pch_Generate_opencv_test_videoio.dir/clean

modules/videoio/CMakeFiles/pch_Generate_opencv_test_videoio.dir/depend:
	cd /home/babak/Desktop/open_cv/opencv-3.4.1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/babak/Desktop/open_cv/opencv-3.4.1 /home/babak/Desktop/open_cv/opencv-3.4.1/modules/videoio /home/babak/Desktop/open_cv/opencv-3.4.1/build /home/babak/Desktop/open_cv/opencv-3.4.1/build/modules/videoio /home/babak/Desktop/open_cv/opencv-3.4.1/build/modules/videoio/CMakeFiles/pch_Generate_opencv_test_videoio.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : modules/videoio/CMakeFiles/pch_Generate_opencv_test_videoio.dir/depend

