TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    matrix_source.cpp \
    functions_source.cpp \
    get_from_std_istram.cpp \
    matrix_main.cpp

HEADERS += \
    functions_headers.h \
    matrix_headers.h \
    get_from_std_istram.h \
    stream_defines.h
