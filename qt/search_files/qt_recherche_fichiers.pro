# -------------------------------------------------
# Project created by QtCreator 2013-05-03T19:30:30
# -------------------------------------------------
TARGET = RechercheDeFichiers
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    thread.cpp \
    dialog.cpp \
    threadmodif.cpp \
    mesthread.cpp
HEADERS += mainwindow.h \
    thread.h \
    dialog.h \
    threadmodif.h \
    mesthread.h
FORMS += mainwindow.ui \
    dialog.ui
#CONFIG += console debug
QT += xml widgets

#QMAKE_UIC = /usr/lib/x86_64-linux-gnu/qt5/bin/uic

RESOURCES += ress.qrc

