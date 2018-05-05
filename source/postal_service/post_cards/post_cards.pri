

HEADERS += $${WORKSPACE}/postal_service/ipost_card.h
HEADERS += $${WORKSPACE}/postal_service/post_cards/test_post_card.h

SOURCES += $${WORKSPACE}/schema/compiled_files/test_proto.pb.cc

LIBS += /usr/local/lib/libprotobuf.a \
        /usr/local/lib/libprotoc.a \
        /usr/local/lib/libprotobuf-lite.a\
        $${WORKSPACE}/external_libraries/googletest/lib/libgtest.a
