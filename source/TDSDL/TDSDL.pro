﻿DEFINES += _WIN32 WIN32 \
           _UNIX UNIX
TEMPLATE = app

QMAKE_CXXFLAGS += -std=gnu++0x
QT += opengl

win32 {
    INCLUDEPATH += "C:\SFML\SFML-2.0\include" \
                   "C:\glew-1.9.0\include"

    LIBS += -L"C:\SFML\SFML-2.0\lib" \
        -lsfml-system \
        -lsfml-window \
        -lsfml-graphics \
        -lsfml-audio \
        -L"C:\glew-1.9.0\lib" \
        -lglew32 \
        -lglu32 \
        -L"C:\box2d\lib" \
        -llibBox2D
}

unix {
    LIBS += -L/usr/local/lib/ -lsfml-graphics -lBox2D

    INCLUDEPATH += /usr/local/include
    DEPENDPATH += /usr/local/include

    PRE_TARGETDEPS += /usr/local/lib/libBox2D.a
}

HEADERS += \
    LTBL/ShadowFin.h \
    LTBL/SFML_OpenGL.h \
    LTBL/QuadTreeOccupant.h \
    LTBL/QuadTreeNode.h \
    LTBL/QuadTree.h \
    LTBL/LightSystem.h \
    LTBL/Light_Beam.h \
    LTBL/Light.h \
    LTBL/ConvexHull.h \
    LTBL/Constructs.h \
    control.h \
    resources.h \
    animation.h \
    entity.h \
    unit.h \
    physics.h \
    contactlistener.h \
    app.h

SOURCES += \
    main.cpp \
    LTBL/ShadowFin.cpp \
    LTBL/SFML_OpenGL.cpp \
    LTBL/QuadTreeOccupant.cpp \
    LTBL/QuadTreeNode.cpp \
    LTBL/QuadTree.cpp \
    LTBL/LightSystem.cpp \
    LTBL/Light_Beam.cpp \
    LTBL/Light.cpp \
    LTBL/ConvexHull.cpp \
    LTBL/Constructs.cpp \
    control.cpp \
    animation.cpp \
    entity.cpp \
    unit.cpp \
    physics.cpp \
    contactlistener.cpp \
    app.cpp
