﻿TEMPLATE = app

QMAKE_CXXFLAGS += -std=gnu++0x
QT += opengl

win32 {
    INCLUDEPATH += "C:/SFML/SFML-2.0/include" \
                   "C:/glew-1.9.0/include" \
                   "C:/cegui/include/cegui-0"

    LIBS += -L"C:/SFML/SFML-2.0/lib" \
        -lsfml-system \
        -lsfml-window \
        -lsfml-graphics \
        -lsfml-audio \
        -L"C:/glew-1.9.0/lib" \
        -lglew32 \
        -lglu32 \
        -L"C:/box2d/lib" \
        -llibBox2D \
        -L"C:/cegui/lib" \
        -llibCEGUIBase-0 \
        -llibCEGUIOpenGLRenderer-0
}

unix {
    LIBS += -L/usr/local/lib/  \
            -lsfml-system \
            -lsfml-graphics \
            -lsfml-audio \
            -lsfml-window \
            -lBox2D

    INCLUDEPATH += /usr/local/include
}

HEADERS += \
    resources.h \
    app.h \
    LTBL/Constructs.h \
    LTBL/Constructs/Vec2f.h \
    LTBL/Constructs/Point2i.h \
    LTBL/Constructs/Color3f.h \
    LTBL/Constructs/AABB.h \
    LTBL/Light/ShadowFin.h \
    LTBL/Light/LightSystem.h \
    LTBL/Light/Light_Point.h \
    LTBL/Light/Light.h \
    LTBL/Light/EmissiveLight.h \
    LTBL/Light/ConvexHull.h \
    LTBL/QuadTree/StaticQuadTree.h \
    LTBL/QuadTree/QuadTreeOccupant.h \
    LTBL/QuadTree/QuadTreeNode.h \
    LTBL/QuadTree/QuadTree.h \
    Physics/physics.h \
    Physics/contactlistener.h \
    Entity/unit.h \
    Entity/entity.h \
    Entity/control.h \
    Entity/animation.h

SOURCES += \
    app.cpp \
    main.cpp \
    LTBL/Constructs/Vec2f.cpp \
    LTBL/Constructs/Point2i.cpp \
    LTBL/Constructs/Color3f.cpp \
    LTBL/Constructs/AABB.cpp \
    LTBL/Light/ShadowFin.cpp \
    LTBL/Light/LightSystem.cpp \
    LTBL/Light/Light_Point.cpp \
    LTBL/Light/Light.cpp \
    LTBL/Light/EmissiveLight.cpp \
    LTBL/Light/ConvexHull.cpp \
    LTBL/QuadTree/StaticQuadTree.cpp \
    LTBL/QuadTree/QuadTreeOccupant.cpp \
    LTBL/QuadTree/QuadTreeNode.cpp \
    LTBL/QuadTree/QuadTree.cpp \
    Physics/physics.cpp \
    Physics/contactlistener.cpp \
    Entity/unit.cpp \
    Entity/entity.cpp \
    Entity/control.cpp \
    Entity/animation.cpp
