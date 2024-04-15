QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    canbus.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix:!macx: LIBS += -L$$PWD/./ -lcanbus

INCLUDEPATH += $$PWD/''
DEPENDPATH += $$PWD/''

unix:!macx: PRE_TARGETDEPS += $$PWD/./libcanbus.a

unix:!macx: LIBS += -L$$PWD/./ -lusb-1.0

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

unix:!macx: PRE_TARGETDEPS += $$PWD/./libusb-1.0.a
