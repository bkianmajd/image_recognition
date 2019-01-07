!contains(included_modules, $$PWD ) {
included_modules += $$PWD

HEADERS += $${WORKSPACE}/components/poker/poker_game_controller/training/training_game_controller.h

SOURCES += $${WORKSPACE}/components/poker/poker_game_controller/training/training_game_controller.cpp

include($${WORKSPACE}/components/poker/poker_game_controller/poker_game_controller.pri)
include($${WORKSPACE}/components/poker/entities/entities.pri)
include($${WORKSPACE}/helpers/file_manager/file_manager.pri)
include($${WORKSPACE}/libraries/image_trainer/image_trainer.pri)
include($${WORKSPACE}/libraries/image_pipeline/image_pipeline.pri)
}
