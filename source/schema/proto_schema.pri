QT += core
QT += network

HEADERS += $${WORKSPACE}/schema/compiled_files/*.h

SOURCES += $${WORKSPACE}/schema/compiled_files/*.cc

INCLUDEPATH += $${WORKSPACE}/external_libraries/protobuf/src

LIBS += /usr/local/lib/libprotobuf.a \
        /usr/local/lib/libprotoc.a \
        /usr/local/lib/libprotobuf-lite.a

