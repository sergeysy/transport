TEMPLATE =	lib

CONFIG += c++14

INCLUDEPATH += "include"

TARGET =	transport

HEADERS +=	include/transport.hpp

SOURCES +=      sources/transport.cpp

# source code encoding
QMAKE_CXXFLAGS += -finput-charset="UTF-8"