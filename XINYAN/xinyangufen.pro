######################################################################
# Automatically generated by qmake (2.01a) ?? 3? 14 16:25:04 2017
######################################################################

QT += sql
LIBS += -L./hwlib -lcamera_interface
LIBS += -L ./hwlib -lshm

TEMPLATE = app
TARGET = 
DEPENDPATH += . hwlib
INCLUDEPATH += . hwlib

# Input
HEADERS += widget.h \
           hwlib/camera_interface_new.h \
           hwlib/libshm.h \
           hwlib/videodevice.h
FORMS += widget.ui
SOURCES += main.cpp widget.cpp
RESOURCES += xinyanqrc.qrc
