VERSION = 0.0.2

folder_01.source = qml/arek
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

QML_IMPORT_PATH =

symbian:TARGET.UID3 = 0xE0FBD61C
symbian:TARGET.CAPABILITY += NetworkServices

QT += network
QT += script
CONFIG += mobility
CONFIG += qdeclarative-boostable
CONFIG += qt-components
MOBILITY += sensors

SOURCES += main.cpp \
    counter.cpp \
    logger.cpp

include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog

HEADERS += \
    counter.h \
    logger.h
