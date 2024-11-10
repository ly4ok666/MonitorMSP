QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    initbasicstyle.cpp \
    main.cpp \
    mainwindow.cpp \
    mytcpsocket.cpp \
    qcustomplot.cpp \
    systemlogger.cpp \
    tric.cpp \
    tsap.cpp \
    tvsk.cpp

HEADERS += \
    SPI.h \
    TCP.h \
    Targets.h \
    initbasicstyle.h \
    mainwindow.h \
    mytcpsocket.h \
    qcustomplot.h \
    systemlogger.h \
    tric.h \
    tsap.h \
    tvsk.h

FORMS += \
    mainwindow.ui \
    tric.ui \
    tsap.ui \
    tvsk.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    tempRes.qrc
