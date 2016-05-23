#-------------------------------------------------
#
# Project created by QtCreator 2015-07-11T10:57:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = IgraVsHuman
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ship.cpp \
    game.cpp \
    cell.cpp \
    enemy_scene.cpp \
    my_scene.cpp \
    choose_level.cpp \
    scenes.cpp

HEADERS  += mainwindow.h \
    ship.h \
    game.h \
    const.h \
    cell.h \
    enemy_scene.h \
    my_scene.h \
    choose_level.h \
    scenes.h

FORMS    += mainwindow.ui \
    choose_level.ui
