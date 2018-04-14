#include path
INCLUDEPATH +=  $${WORKSPACE}/ \
                $${WORKSPACE}/external_libraries/opencv-3.4.1/include


# Kuka rbd test
HEADERS += $${WORKSPACE}/rpc_image/rpc_server/rpc_server.h \
           $${WORKSPACE}/schema/compiled_files/template_match.grpc.pb.h

SOURCES += $${WORKSPACE}/schema/compiled_files/template_match.grpc.pb.cc \
           $${WORKSPACE}/schema/compiled_files/template_match.pb.cc

LIBS += /usr/local/lib/libprotobuf.a \
/usr/local/lib/libprotoc.a \
/usr/local/lib/libprotobuf-lite.a \
/usr/local/lib/libgrpc.a \
/usr/local/lib/libgrpc++.a
