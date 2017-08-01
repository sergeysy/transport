TEMPLATE =	lib

#MAKEFLAGS="-j8"

CONFIG += c++14

INCLUDEPATH += "$$_PRO_FILE_PWD_/include"
INCLUDEPATH += "$$LIB_SETTINGS_DIR/include"

TARGET = $$LIBTRANSPORT

HEADERS +=	include/transport.hpp

SOURCES +=      sources/transport.cpp

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
