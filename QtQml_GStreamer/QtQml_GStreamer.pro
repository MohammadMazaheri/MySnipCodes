QT += quick multimedia

HEADERS += \
    videoserver.h

SOURCES += \
        main.cpp \
        videoserver.cpp

RESOURCES += qml.qrc

LIBS += -L/usr/lib/x86_64-linux-gnu -lgstreamer-1.0 -lgstvideo-1.0  -lgstbase-1.0 -lglib-2.0 -lgobject-2.0
INCLUDEPATH += /usr/include/gstreamer-1.0
DEPENDPATH += /usr/include/gstreamer-1.0
INCLUDEPATH += /usr/include/glib-2.0
DEPENDPATH += /usr/include/glib-2.0
INCLUDEPATH += /usr/lib/x86_64-linux-gnu/glib-2.0/include
DEPENDPATH += /usr/lib/x86_64-linux-gnu/glib-2.0/include
