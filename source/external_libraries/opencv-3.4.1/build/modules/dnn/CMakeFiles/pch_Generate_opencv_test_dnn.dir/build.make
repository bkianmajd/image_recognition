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

# Utility rule file for pch_Generate_opencv_test_dnn.

# Include the progress variables for this target.
include modules/dnn/CMakeFiles/pch_Generate_opencv_test_dnn.dir/progress.make

modules/dnn/CMakeFiles/pch_Generate_opencv_test_dnn: modules/dnn/test_precomp.hpp.gch/opencv_test_dnn_Release.gch


modules/dnn/test_precomp.hpp.gch/opencv_test_dnn_Release.gch: ../modules/dnn/test/test_precomp.hpp
modules/dnn/test_precomp.hpp.gch/opencv_test_dnn_Release.gch: modules/dnn/test_precomp.hpp
modules/dnn/test_precomp.hpp.gch/opencv_test_dnn_Release.gch: lib/libopencv_test_dnn_pch_dephelp.a
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/babak/Desktop/open_cv/opencv-3.4.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating test_precomp.hpp.gch/opencv_test_dnn_Release.gch"
	cd /home/babak/Desktop/open_cv/opencv-3.4.1/build/modules/dnn && /usr/bin/cmake -E make_directory /home/babak/Desktop/open_cv/opencv-3.4.1/build/modules/dnn/test_precomp.hpp.gch
	cd /home/babak/Desktop/open_cv/opencv-3.4.1/build/modules/dnn && /usr/bin/c++ -O3 -DNDEBUG -DNDEBUG "-D__OPENCV_BUILD=1" "-D_USE_MATH_DEFINES" "-D__STDC_CONSTANT_MACROS" "-D__STDC_LIMIT_MACROS" "-D__STDC_FORMAT_MACROS" "-DHAVE_PROTOBUF=1" "-D__OPENCV_TESTS=1" -I"/home/babak/Desktop/open_cv/opencv-3.4.1/build/3rdparty/ippicv/ippicv_lnx/include" -I"/home/babak/Desktop/open_cv/opencv-3.4.1/build/3rdparty/ippicv/ippiw_lnx/include" -I"/home/babak/Desktop/open_cv/opencv-3.4.1/build" -I"/home/babak/Desktop/open_cv/opencv-3.4.1/build/3rdparty/ippicv/ippicv_lnx/include" -I"/home/babak/Desktop/open_cv/opencv-3.4.1/build/3rdparty/ippicv/ippiw_lnx/include" -I"/home/babak/Desktop/open_cv/opencv-3.4.1/build" -I"/home/babak/Desktop/open_cv/opencv-3.4.1/modules/ts/include" -I"/home/babak/Desktop/open_cv/opencv-3.4.1/modules/dnn/include" -I"/home/babak/Desktop/open_cv/opencv-3.4.1/modules/imgcodecs/include" -I"/home/babak/Desktop/open_cv/opencv-3.4.1/modules/videoio/include" -I"/home/babak/Desktop/open_cv/opencv-3.4.1/modules/core/include" -I"/home/babak/Desktop/open_cv/opencv-3.4.1/modules/imgproc/include" -I"/home/babak/Desktop/open_cv/opencv-3.4.1/modules/core/include" -I"/home/babak/Desktop/open_cv/opencv-3.4.1/modules/imgproc/include" -I"/home/babak/Desktop/open_cv/opencv-3.4.1/modules/imgcodecs/include" -I"/home/babak/Desktop/open_cv/opencv-3.4.1/modules/videoio/include" -I"/home/babak/Desktop/open_cv/opencv-3.4.1/modules/highgui/include" -I"/home/babak/Desktop/open_cv/opencv-3.4.1/modules/dnn/test" -fsigned-char -W -Wall -Werror=return-type -Werror=address -Werror=sequence-point -Wformat -Werror=format-security -Winit-self -Wpointer-arith -Wuninitialized -Winit-self -Wno-narrowing -Wno-delete-non-virtual-dtor -Wno-comment -fdiagnostics-show-option -Wno-long-long -pthread -fomit-frame-pointer -ffunction-sections -fdata-sections -msse -msse2 -msse3 -fvisibility=hidden -fvisibility-inlines-hidden -Wno-shadow -Wno-parentheses -Wno-maybe-uninitialized -Wno-sign-promo -Wno-missing-declarations -Wno-deprecated -Wno-missing-declarations -Wno-shadow -Wno-unused-parameter -Wno-unused-local-typedefs -Wno-sign-compare -Wno-sign-promo -Wno-undef -Wno-ignored-qualifiers -Wno-extra -Wno-unused-function -Wno-deprecated-declarations -Wno-error=non-virtual-dtor -Wno-unused-parameter -Wno-undef -Wno-ignored-qualifiers -Wno-enum-compare -Wno-deprecated-declarations -Wno-invalid-offsetof -fPIE -x c++-header -o /home/babak/Desktop/open_cv/opencv-3.4.1/build/modules/dnn/test_precomp.hpp.gch/opencv_test_dnn_Release.gch /home/babak/Desktop/open_cv/opencv-3.4.1/build/modules/dnn/test_precomp.hpp

modules/dnn/test_precomp.hpp: ../modules/dnn/test/test_precomp.hpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/babak/Desktop/open_cv/opencv-3.4.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating test_precomp.hpp"
	cd /home/babak/Desktop/open_cv/opencv-3.4.1/build/modules/dnn && /usr/bin/cmake -E copy_if_different /home/babak/Desktop/open_cv/opencv-3.4.1/modules/dnn/test/test_precomp.hpp /home/babak/Desktop/open_cv/opencv-3.4.1/build/modules/dnn/test_precomp.hpp

pch_Generate_opencv_test_dnn: modules/dnn/CMakeFiles/pch_Generate_opencv_test_dnn
pch_Generate_opencv_test_dnn: modules/dnn/test_precomp.hpp.gch/opencv_test_dnn_Release.gch
pch_Generate_opencv_test_dnn: modules/dnn/test_precomp.hpp
pch_Generate_opencv_test_dnn: modules/dnn/CMakeFiles/pch_Generate_opencv_test_dnn.dir/build.make

.PHONY : pch_Generate_opencv_test_dnn

# Rule to build all files generated by this target.
modules/dnn/CMakeFiles/pch_Generate_opencv_test_dnn.dir/build: pch_Generate_opencv_test_dnn

.PHONY : modules/dnn/CMakeFiles/pch_Generate_opencv_test_dnn.dir/build

modules/dnn/CMakeFiles/pch_Generate_opencv_test_dnn.dir/clean:
	cd /home/babak/Desktop/open_cv/opencv-3.4.1/build/modules/dnn && $(CMAKE_COMMAND) -P CMakeFiles/pch_Generate_opencv_test_dnn.dir/cmake_clean.cmake
.PHONY : modules/dnn/CMakeFiles/pch_Generate_opencv_test_dnn.dir/clean

modules/dnn/CMakeFiles/pch_Generate_opencv_test_dnn.dir/depend:
	cd /home/babak/Desktop/open_cv/opencv-3.4.1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/babak/Desktop/open_cv/opencv-3.4.1 /home/babak/Desktop/open_cv/opencv-3.4.1/modules/dnn /home/babak/Desktop/open_cv/opencv-3.4.1/build /home/babak/Desktop/open_cv/opencv-3.4.1/build/modules/dnn /home/babak/Desktop/open_cv/opencv-3.4.1/build/modules/dnn/CMakeFiles/pch_Generate_opencv_test_dnn.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : modules/dnn/CMakeFiles/pch_Generate_opencv_test_dnn.dir/depend
