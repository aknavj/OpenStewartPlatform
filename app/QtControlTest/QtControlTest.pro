QT += widgets

TEMPLATE = app
TARGET = QtControlTest
DESTDIR = ./

QMAKE_LFLAGS += /INCREMENTAL:NO

HEADERS += \
    QtAdjRangeSlider.h \
    QtMovesWindow.h \
    QtSerialConnection.h \
    QtWindow.h

SOURCES += \
    QtAdjRangeSlider.cpp \
    QtMovesWindow.cpp \
    QtSerialConnection.cpp \
    QtWindow.cpp \
    Qtmain.cpp
