#-------------------------------------------------
#
# Project created by QtCreator 2019-09-27T16:04:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FishTank
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    treeView.cpp \
    dialogstruct.cpp \
    dialogfile.cpp \
    dialogprocess.cpp \
    int3listing.cpp \
    int3thread.cpp \
    process.cpp \
    process_thread.cpp \
    process_thread_lisn.cpp

HEADERS += \
        mainwindow.h \
    dialogstruct.h \
    dialogfile.h \
    dialogprocess.h \
    int3thread.h \
    process.h \
    processthread.h

FORMS += \
        mainwindow.ui \
    dialogstruct.ui \
    dialogfile.ui \
    dialogprocess.ui

RESOURCES += \
    myres.qrc


unix|win32: LIBS += -lvmi
