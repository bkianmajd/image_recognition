!contains(included_modules, $$_FILE_) {
included_modules += $$_FILE_

QMAKE_CXXFLAGS += -fno-exceptions

INCLUDEPATH += $${WORKSPACE}/external_libraries/libchrome
INCLUDEPATH += $${WORKSPACE}/external_libraries/libchrome/base/third_party

#INCLUDEPATH += $${WORKSPACE}/external_libraries/libchrome/third_party/tcmalloc/gperftools-2.0/chromium/src

SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/process/process_metrics_linux.cc
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/process/process_metrics_posix.cc
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/process/process_metrics.cc
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/process/process_posix.cc
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/process/process_handle_posix.cc
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/process/kill_posix.cc
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/process/launch_posix.cc
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/process/process_handle_linux.cc
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/process/process_iterator.cc
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/process/process_iterator_linux.cc
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/process/kill.cc
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/process/internal_linux.cc
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/process/memory.cc
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/process/memory_linux.cc
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/process/process_handle.cc

SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/*.cc
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/synchronization/*.cc
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/memory/*.cc
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/strings/*.cc
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/files/*.cc
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/debug/*.cc
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/posix/*.cc
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/time/*.cc
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/threading/*.cc
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/trace_event/*.cc
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/metrics/*.cc
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/nix/*.cc
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/json/*.cc
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/timer/*.cc
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/message_loop/*.cc
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/system/*.cc
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/task/*.cc
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/task/sequence_manager/*.cc
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/task/common/*.cc
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/task/task_scheduler/*.cc


#SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/test/*.cc

SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/allocator/allocator_shim.cc
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/allocator/allocator_shim_default_dispatch_to_glibc.cc

SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/third_party/modp_b64/*.cc
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/third_party/superfasthash/superfasthash.c
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/third_party/icu/icu_utf.cc
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/third_party/dmg_fp/g_fmt.cc
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/third_party/dmg_fp/dtoa.cc
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/third_party/dmg_fp/dtoa_wrapper.cc
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/third_party/nspr/prtime.cc
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/third_party/xdg_mime/*.c
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/third_party/xdg_user_dirs/xdg_user_dir_lookup.cc
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/third_party/libevent/event.c
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/third_party/libevent/log.c
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/third_party/libevent/evutil.c
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/third_party/libevent/signal.c
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/third_party/libevent/epoll.c
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/third_party/libevent/poll.c
SOURCES += $${WORKSPACE}/external_libraries/libchrome/base/third_party/libevent/select.c



LIBS += /usr/lib/x86_64-linux-gnu/libdl.so
}
