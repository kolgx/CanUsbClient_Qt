QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CanCode/src/CanDrive.cpp \
    CanCode/src/SignalUnit.cpp \
    main.cpp \
    mainwindow.cpp \
    widget/devicemgr/devicemgrform.cpp \
    widget/menu/menuform.cpp \
    widget/signalmonitor/signalitemform.cpp \
    widget/signalmonitor/signalmonitorform.cpp

HEADERS += \
    CanCode/inc/CanDrive.hpp \
    CanCode/inc/CanMsg.hpp \
    CanCode/inc/FIleMgr.hpp \
    CanCode/inc/MainProccess.hpp \
    CanCode/inc/SignalUnit.hpp \
    CanCode/inc/TestList.h \
    CanCode/inc/UI.hpp \
    canbus.h \
    mainwindow.h \
    widget/devicemgr/devicemgrform.h \
    widget/menu/menuform.h \
    widget/signalmonitor/signalitemform.h \
    widget/signalmonitor/signalmonitorform.h

FORMS += \
    mainwindow.ui \
    widget/devicemgr/devicemgrform.ui \
    widget/menu/menuform.ui \
    widget/signalmonitor/signalitemform.ui \
    widget/signalmonitor/signalmonitorform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix:!macx: LIBS += -L$$PWD/./ -lcanbus -lusb-1.0 -ludev
