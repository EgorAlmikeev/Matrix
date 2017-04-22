TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    functions_source.cpp

HEADERS += \
    functions_headers.h \
    get_from_std_istream.h \
    matrix.h \
    stream_defines.h
