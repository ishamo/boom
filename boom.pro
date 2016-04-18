#-------------------------------------------------
#
# Project created by QtCreator 2016-04-13T20:26:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = boom
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    selfcheck.cpp \
    argsetup.cpp \
    record.cpp \
    player.cpp \
    telegram.cpp \
    file.cpp \
    selectpath.cpp

HEADERS  += mainwindow.h \
    selfcheck.h \
    argsetup.h \
    record.h \
    player.h \
    telegram.h \
    file.h \
    selectpath.h

FORMS    += mainwindow.ui \
    selfcheck.ui \
    argsetup.ui \
    record.ui \
    player.ui \
    telegram.ui \
    file.ui \
    selectpath.ui
