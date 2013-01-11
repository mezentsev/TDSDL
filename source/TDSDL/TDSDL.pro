SOURCES += \
    main.cpp \
    app.cpp \
    entity.cpp \
    #e_tower.cpp \
    #e_enemy.cpp \
    animation.cpp \
    map.cpp \
    #e_ground.cpp \
    #control.cpp

win32 {
    INCLUDEPATH += "C:\SFML\SFML-1.6\include"

    LIBS += -L"C:\SFML\SFML-1.6\lib" \
        -llibsfml-main \
        -llibsfml-system \
        -llibsfml-window \
        -llibsfml-graphics

}

DEFINES += _WIN32 WIN32
TEMPLATE = app

HEADERS += \
    app.h \
    entity.h \
    #e_tower.h \
    #e_enemy.h \
    animation.h \
    resources.h \
    map.h \
  #  e_ground.h \
    #control.h
