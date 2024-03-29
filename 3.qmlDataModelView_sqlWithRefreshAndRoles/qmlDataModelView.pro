QT += quick widgets core gui sql quickcontrols2

CONFIG += c++11 qmltypes qt

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp

RESOURCES += qml.qrc

QML_IMPORT_PATH =

QML_DESIGNER_IMPORT_PATH =

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    dbconnection.hpp \
    dbinterface.hpp \
    sqlquerymodel.hpp
