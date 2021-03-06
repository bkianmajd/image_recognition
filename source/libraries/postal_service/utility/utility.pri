!contains(included_modules, $$PWD ) {
  included_modules += $$PWD

HEADERS += $${WORKSPACE}/libraries/postal_service/ipost_card.h
HEADERS += $${WORKSPACE}/libraries/postal_service/utility/test_post_card.h
HEADERS += $${WORKSPACE}/libraries/postal_service/utility/post_card_queue.h
HEADERS += $${WORKSPACE}/libraries/postal_service/utility/mail_distributor_simple.h
HEADERS += $${WORKSPACE}/libraries/postal_service/utility/mail_distributor_queue.h

SOURCES += $${WORKSPACE}/libraries/postal_service/utility/post_card_queue.cpp
SOURCES += $${WORKSPACE}/libraries/postal_service/utility/mail_distributor_simple.cpp
SOURCES += $${WORKSPACE}/libraries/postal_service/utility/mail_distributor_queue.cpp

include($${WORKSPACE}/external_libraries/protobuf_output/protobuf_output.pri)
}
