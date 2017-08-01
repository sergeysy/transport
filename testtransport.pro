TEMPLATE =	app

CONFIG += c++14

INCLUDEPATH += "$$_PRO_FILE_PWD_/include" \
		"$$ROOT_DIR/3rd_party/googletest/googletest/include" \
		"$$ROOT_DIR/submodules/settings/include"

TARGET =	testtransport

HEADERS +=	include/transport.hpp
DEPENDPATH += $$ROOT_DIR/3rd_party/googletest/googletest/include
INCLUDEPATH += $$ROOT_DIR/3rd_party/googletest/googletest/include
PRE_TARGETDEPS += $$ROOT_DIR/3rd_party/googletest/googletest/make/gtest_main.a
#message( $$ROOT_DIR);
#message( $$HEADERS)

SOURCES +=      tests/testtransport.cpp

CONFIG(debug, debug|release) {
    DESTDIR = $$ROOT_DIR/build/debug/$$TARGET
} else {
    DESTDIR = $$ROOT_DIR/build/release/$$TARGET
}

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.u

# source code encoding
QMAKE_CXXFLAGS += -finput-charset="UTF-8"

message($$LD_LIBRARY_PATH)

LIBS += -L"$$ROOT_DIR/3rd_party/googletest/build/googlemock/gtest" -l"libgtest"
#LIBS += -L"$$ROOT_DIR/3rd_party/googletest/googlemock/gtest" -l"libgtest_main"
#LIBS += -L"$$ROOT_DIR/build/release/settings" -l"settings"
#LIBS += -l$$ROOT_DIR/3rd_party/googletest/googletest/make/gtest_main

#LIBS += -l$$ROOT_DIR/3rd_party/googletest/googletest/make/gtest_main.a
#LIBS += -lgtest_main.a

