!contains(included_modules, $$PWD ) {
included_modules += $$PWD

  INCLUDEPATH += $${WORKSPACE}/external_libraries/opencv-3.4.1/include/
  INCLUDEPATH += $${WORKSPACE}/external_libraries/opencv-3.4.1/modules/highgui/include
  INCLUDEPATH += $${WORKSPACE}/external_libraries/opencv-3.4.1/modules/imgproc/include
  INCLUDEPATH += $${WORKSPACE}/external_libraries/opencv-3.4.1/modules/core/include
  INCLUDEPATH += $${WORKSPACE}/external_libraries/opencv-3.4.1/modules/imgcodecs/include
  INCLUDEPATH += $${WORKSPACE}/external_libraries/opencv-3.4.1/modules/videoio/include

  win32 {
  }

  #!win32 {
  #  LIBS += $${WORKSPACE}/external_libraries/opencv_output/build/lib/libopencv_core.so \
  #      $${WORKSPACE}/external_libraries/opencv_output/build/lib/libopencv_core.so.3.4 \
  #      $${WORKSPACE}/external_libraries/opencv_output/build/lib/libopencv_highgui.so \
  #      $${WORKSPACE}/external_libraries/opencv_output/build/lib/libopencv_imgproc.so \
  #      $${WORKSPACE}/external_libraries/opencv_output/build/lib/libopencv_imgcodecs.so
  #}

#the following line is equivalent to setting the LD_LIBRARY_PATH
LIBPATH = $${WORKSPACE}/external_libraries/opencv_output/build/lib
QMAKE_LFLAGS = -Wl,-rpath,$$LIBPATH

  !win32 {
    LIBS += $${WORKSPACE}/external_libraries/opencv_output/build/lib/libopencv_core.so \
        $${WORKSPACE}/external_libraries/opencv_output/build/lib/libopencv_highgui.so \
        $${WORKSPACE}/external_libraries/opencv_output/build/lib/libopencv_imgproc.so \
        $${WORKSPACE}/external_libraries/opencv_output/build/lib/libopencv_imgcodecs.so
  }
}
