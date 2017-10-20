TEMPLATE =	lib

win32|win64 {
DEFINES += CURL_STATICLIB
}
CONFIG += c++14
CONFIG += staticlib

INCLUDEPATH += "$$_PRO_FILE_PWD_/include"
INCLUDEPATH += "$$LIB_SETTINGS_DIR/include"
INCLUDEPATH += "$$LIB_UTILS_DIR/include"
INCLUDEPATH += 	"$$ROOT_DIR/3rd_party/curl/include"
win32 {
INCLUDEPATH += "$(BOOST_ROOT)"
}

TARGET = "$$LIBTRANSPORT"

HEADERS +=	include/transport.hpp
HEADERS +=	"$$ROOT_DIR/3rd_party/curl/include"

SOURCES +=      sources/transport.cpp

CONFIG(debug, debug|release) {
    DESTDIR = "$$ROOT_DIR/build/debug/$$TARGET"
} else {
    DESTDIR = "$$ROOT_DIR/build/release/$$TARGET"
}

OBJECTS_DIR = \""$$DESTDIR/.obj\""

win32 {
LIBS += -L"D:\Projects\validator\3rd_party\curl\build\Win32\VC14\LIB Debug"
}
win32 {
LIBS += -llibcurld
}
unix {
LIBS += -lcurl
}

# source code encoding
QMAKE_CXXFLAGS += -finput-charset="UTF-8"
unix {
QMAKE_CXXFLAGS += -Werror
QMAKE_CXXFLAGS += -Wall
}
