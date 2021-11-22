QT       += core gui \
            serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chatwidget.cpp \
    coder.cpp \
    customwidget.cpp \
    debugthread.cpp \
    filemessage.cpp \
    main.cpp \
    joindialog.cpp \
    mainwindow.cpp \
    mycombobox.cpp \
    qnchatmessage.cpp

HEADERS += \
    chatwidget.h \
    coder.h \
    config.h \
    customwidget.h \
    debugthread.h \
    filemessage.h \
    joindialog.h \
    mainwindow.h \
    mycombobox.h \
    qnchatmessage.h


FORMS += \
    chatwidget.ui \
    customwidget.ui \
    filemessage.ui \
    joindialog.ui \
    mainwindow.ui

TRANSLATIONS += \
    serial_ports_communicate_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    image.qrc
