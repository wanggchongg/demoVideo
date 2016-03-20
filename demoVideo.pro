#-------------------------------------------------
#
# Project created by QtCreator 2015-03-10T11:22:26
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = demoVideo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    decode_func.cpp \
    display_func.cpp \
    matrix.cpp \
    raptorcode.cpp \

HEADERS  += mainwindow.h \
    externvar.h \
    decode_func.h \
    display_func.h \
    matrix.h \
    raptorcode.h \
    def.h \
    sdkddkver.h \
    StdAfx.h \
    targetver.h \

FORMS    += mainwindow.ui

LIBS     += -lWs2_32

INCLUDEPATH += SDL/include
LIBS += SDL/lib/libSDL.dll.a

INCLUDEPATH += ffmpeg/include
LIBS += ffmpeg/lib/libavcodec.dll.a \
        ffmpeg/lib/libavdevice.dll.a \
        ffmpeg/lib/libavfilter.dll.a \
        ffmpeg/lib/libavformat.dll.a \
        ffmpeg/lib/libavutil.dll.a \
        ffmpeg/lib/libpostproc.dll.a \
        ffmpeg/lib/libswscale.dll.a \


