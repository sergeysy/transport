TEMPLATE =	lib

#MAKEFLAGS="-j8"

CONFIG += c++14

INCLUDEPATH += "$$_PRO_FILE_PWD_/include"

TARGET =	transport

HEADERS +=	include/transport.hpp

SOURCES +=      sources/transport.cpp

CONFIG(debug, debug|release) {
    #DESTDIR = ../build/debug/$$TARGET
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
