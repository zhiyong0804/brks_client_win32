#-------------------------------------------------
#
# Project created by QtCreator 2018-06-11T14:52:16
#
#-------------------------------------------------

QT       += core gui sql
QT       += webengine webenginewidgets
QT       += multimedia multimediawidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mobike
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

#INCLUDEPATH +=$$PWD JQQRCodeReader
#INCLUDEPATH +=$$PWD/JQQRCodeReader/include/JQQRCodeReader
#include($$PWD/JQQRCodeReader/JQQRCodeReader.pri)

include(QZXing/QZXing.pri)

INCLUDEPATH +=$$PWD db
include($$PWD/db/db.pri)

INCLUDEPATH +=$$PWD user
include($$PWD/user/user.pri)


SOURCES += \
        main.cpp \
        homewindow.cpp \
    bikemapview.cpp \
    logindialog.cpp \
    scanqrcodedialog.cpp \
    thread.cpp \
    worker.cpp \
    timerutil.cpp \
    userdialog.cpp \
    unlockdialog.cpp \
    ttkcircularprogresswidget.cpp \
    qrcodecameraviewfinder.cpp \
    qrcodedecodethread.cpp \
    triplistdialog.cpp \
    oneride.cpp \
    moneydialog.cpp \
    rechargedialog.cpp \
    costbutton.cpp \
    confirmrechardialog.cpp \
    ../../../../../work/media-develop/ffmpeg/LQF-Media/LQFToolKit/src/thread/list.cpp

HEADERS += \
        homewindow.h \
    ui_style_sheet.h \
    bikemapview.h \
    logindialog.h \
    config.h \
    scanqrcodedialog.h \
    thread.h \
    worker.h \
    timerutil.h \
    userdialog.h \
    unlockdialog.h \
    ttkcircularprogresswidget.h \
    ttkglobaldefine.h \
    qrcodecameraviewfinder.h \
    qrcodedecodethread.h \
    triplistdialog.h \
    oneride.h \
    moneydialog.h \
    rechargedialog.h \
    costbutton.h \
    confirmrechardialog.h \
    ../../../../../work/media-develop/ffmpeg/LQF-Media/LQFToolKit/src/thread/list.h

FORMS += \
        homewindow.ui \
    logindialog.ui \
    scanqrcodedialog.ui \
    userdialog.ui \
    unlockdialog.ui \
    triplistdialog.ui \
    moneydialog.ui \
    rechargedialog.ui \
    confirmrechardialog.ui

RESOURCES += \
    image/image.qrc
RC_FILE = myapp.rc
