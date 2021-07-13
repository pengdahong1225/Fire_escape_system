#-------------------------------------------------
#
# Project created by QtCreator 2021-05-14T10:56:47
#
#-------------------------------------------------
#模块
QT       += core gui
QT += network
QT += axcontainer
QT += sql
QT       += multimedia multimediawidgets
RC_ICONS = car.ico


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
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

CONFIG += c++11

SOURCES += \
        add_fireman.cpp \
        fun_sql.cpp \
        help_router.cpp \
        main.cpp \
        main_login.cpp \
        mainwindow.cpp \
        udpthread.cpp

HEADERS += \
        add_fireman.h \
        fun_sql.h \
        help_router.h \
        main_login.h \
        mainwindow.h \
        udpthread.h

FORMS += \
        add_fireman.ui \
        help_router.ui \
        main_login.ui \
        mainwindow.ui

INCLUDEPATH += D:\openCV\opencv\build\include \
               D:\openCV\opencv\build\include\opencv2

LIBS += \
    D:\openCV\opencv\build\x64\vc14\lib\opencv_world450d.lib \
    D:\openCV\opencv\build\x64\vc14\lib\opencv_world450.lib

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qrc.qrc
