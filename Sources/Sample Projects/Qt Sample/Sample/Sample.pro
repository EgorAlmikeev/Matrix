TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ../../../Library/functions_source.cpp

HEADERS += \
    ../../../Library/functions_headers.h \
    ../../../Library/get_from_std_istream.h \
    ../../../Library/matrix.h \
    ../../../Library/stream_defines.h
