DEFINES += _WIN32 WIN32 \
           _UNIX UNIX
TEMPLATE = app

win32 {
    INCLUDEPATH += "C:\SFML\SFML-2.0\include" \
                   "C:\BOX2D\include"

    LIBS += -L"C:\SFML\SFML-2.0\lib" \
        -llibsfml-main \
        -llibsfml-system \
        -llibsfml-window \
        -llibsfml-graphics \
        -L"C:\BOX2D\lib" \
        -llibBox2D
}

unix {
    LIBS += -L/usr/local/lib/ -lsfml-graphics -lBox2D

    INCLUDEPATH += /usr/local/include
    DEPENDPATH += /usr/local/include

    PRE_TARGETDEPS += /usr/local/lib/libBox2D.a
}

HEADERS += \
    app.h \
    entity.h \
    #e_tower.h \
    #e_enemy.h \
    animation.h \
    resources.h \
    map.h \
  #  e_ground.h \
    control.h \
    unit.h \
    physics.h

SOURCES += \
    main.cpp \
    app.cpp \
    entity.cpp \
    #e_tower.cpp \
    #e_enemy.cpp \
    animation.cpp \
    map.cpp \
    #e_ground.cpp \
    control.cpp \
    unit.cpp \
    physics.cpp
