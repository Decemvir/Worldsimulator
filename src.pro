#-------------------------------------------------
#
# Project created by QtCreator 2019-07-27T09:18:46
#
#-------------------------------------------------

QT       += core gui designer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = src
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

CONFIG += c++11

SOURCES += \
        main.cpp \
        model/decorator.cpp \
        model/god/alah.cpp \
        model/god/alahExFactory.cpp \
        model/god/cartesianCoordAdapter.cpp \
        model/god/coordinates.cpp \
        model/god/destiny.cpp \
        model/god/deusExFactory.cpp \
        model/god/god.cpp \
        model/god/highDevLF.cpp \
        model/god/jesus.cpp \
        model/god/jesusExFactory.cpp \
        model/god/lifeForm.cpp \
        model/god/lowDefLF.cpp \
        model/god/midDevLF.cpp \
        model/god/planet.cpp \
        model/god/universe.cpp \
        model/god/veryHighDevLF.cpp \
        model/god/veryHighDevLFExFactory.cpp \
        model/humanbreeder/human.cpp \
        model/implementations.cpp \
        simulationwidget.cpp \
        viewcontroller/destinyAdapter.cpp \
        viewcontroller/entity.cpp \
        viewcontroller/godAdapter.cpp \
        viewcontroller/highDevLFEntity.cpp \
        viewcontroller/lfJobHandler.cpp \
        viewcontroller/lfJobs.cpp \
        viewcontroller/lifeformEntity.cpp \
        viewcontroller/lighthandler.cpp \
        viewcontroller/lowDevLFEntity.cpp \
        viewcontroller/midDevLFEntity.cpp \
        viewcontroller/mindworldsgui.cpp \
        viewcontroller/planetEntity.cpp \
        viewcontroller/simwidgetcontroller.cpp \
        viewcontroller/simwidgetdatamodel.cpp \
        viewcontroller/solarSystemEntity.cpp \
        viewcontroller/universeEntity.cpp \
        viewcontroller/viewOfEntities.cpp

HEADERS += \
    model/god/alah.h \
    model/god/alahExFactory.h \
    model/god/cartesianCoordAdapter.h \
    model/god/coordinates.h \
    model/god/destiny.h \
    model/god/deusExFactory.h \
    model/god/god.h \
    model/god/highDevLF.h \
    model/god/jesus.h \
    model/god/jesusExFactory.h \
    model/god/lifeForm.h \
    model/god/lowDevLF.h \
    model/god/midDevLF.h \
    model/god/planet.h \
    model/god/resource.h \
    model/god/universe.h \
    model/god/veryHighDevLF.h \
    model/god/veryHighDevLFExFactory.h \
    model/humanbreeder/human.h \
    model/implementations.h \
    model/interfaces.h \
    simulationwidget.h \
    viewcontroller/destinyAdapter.h \
    viewcontroller/entity.h \
    viewcontroller/godAdapter.h \
    viewcontroller/highDevLFEntity.h \
    viewcontroller/lfJobHandler.h \
    viewcontroller/lfJobs.h \
    viewcontroller/lifeformEntity.h \
    viewcontroller/lighthandler.h \
    viewcontroller/lowDevLFEntity.h \
    viewcontroller/midDevLFEntity.h \
    viewcontroller/mindworldsgui.h \
    viewcontroller/planetEntity.h \
    viewcontroller/simwidgetcontroller.h \
    viewcontroller/simwidgetdatamodel.h \
    viewcontroller/solarSystemEntity.h \
    viewcontroller/universeEntity.h \
    viewcontroller/viewOfEntities.h

FORMS += \
    viewcontroller/mindworldsgui.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    viewcontroller/Resources/Shaders/fshader.glsl \
    viewcontroller/Resources/Shaders/vshader.glsl \
    viewcontroller/Resources/Textures/ReadMe.txt \
    viewcontroller/Resources/Textures/earth.jpg \
    viewcontroller/Resources/Textures/fictional1.jpg \
    viewcontroller/Resources/Textures/fictional2.jpg \
    viewcontroller/Resources/Textures/fictional3.jpg \
    viewcontroller/Resources/Textures/fictional4.jpg \
    viewcontroller/Resources/Textures/jupiter.jpg \
    viewcontroller/Resources/Textures/mars.jpg \
    viewcontroller/Resources/Textures/mercury.jpg \
    viewcontroller/Resources/Textures/moon.jpg \
    viewcontroller/Resources/Textures/neptune.jpg \
    viewcontroller/Resources/Textures/saturn.jpg \
    viewcontroller/Resources/Textures/skybox.jpg \
    viewcontroller/Resources/Textures/sun.jpg \
    viewcontroller/Resources/Textures/uranus.jpg \
    viewcontroller/Resources/Textures/venus.jpg

RESOURCES += \
    viewcontroller/mindworldsgui.qrc \
    viewcontroller/mindworldsgui.qrc
