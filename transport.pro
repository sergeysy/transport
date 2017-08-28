TEMPLATE =	lib

CONFIG += c++14
CONFIG += staticlib

INCLUDEPATH += "$$_PRO_FILE_PWD_/include"
INCLUDEPATH += "$$LIB_SETTINGS_DIR/include"
INCLUDEPATH += "$$LIB_UTILS_DIR/include"

TARGET = "$$LIBTRANSPORT"

HEADERS +=	include/transport.hpp

SOURCES +=      sources/transport.cpp

CONFIG(debug, debug|release) {
    DESTDIR = "$$ROOT_DIR/build/debug/$$TARGET"
} else {
    DESTDIR = "$$ROOT_DIR/build/release/$$TARGET"
}

OBJECTS_DIR = \""$$DESTDIR/.obj\""

LIBS += -lcurl

# source code encoding
QMAKE_CXXFLAGS += -finput-charset="UTF-8"
QMAKE_CXXFLAGS += -Werror
QMAKE_CXXFLAGS += -Wall