

HEADERS += $${WORKSPACE}/postal_service/ipost_card.h
HEADERS += $${WORKSPACE}/postal_service/utility/test_post_card.h
HEADERS += $${WORKSPACE}/postal_service/utility/post_card_queue.h
HEADERS += $${WORKSPACE}/postal_service/utility/mail_distributor_simple.h
HEADERS += $${WORKSPACE}/postal_service/utility/mail_distributor_queue.h

SOURCES += $${WORKSPACE}/postal_service/utility/post_card_queue.cpp
SOURCES += $${WORKSPACE}/postal_service/utility/mail_distributor_simple.cpp
SOURCES += $${WORKSPACE}/postal_service/utility/mail_distributor_queue.cpp

LIBS += /usr/local/lib/libprotobuf.a \
        /usr/local/lib/libprotoc.a \
        /usr/local/lib/libprotobuf-lite.a\
        $${WORKSPACE}/external_libraries/googletest/lib/libgtest.a
