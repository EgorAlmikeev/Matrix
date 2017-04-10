TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    functions_source.cpp \
    matrix_main.cpp

HEADERS += \
    functions_headers.h \
    stream_defines.h \
    get_from_std_istream.h \
    matrix.h
