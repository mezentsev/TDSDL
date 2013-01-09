SOURCES += \
    main.cpp \
    app.cpp \
    sprite.cpp \
    entity.cpp \
    timer.cpp \
    text.cpp \
    e_tower.cpp \
    e_enemy.cpp \
    animation.cpp \
    map.cpp \
    sound.cpp \
    e_ground.cpp \
    camera.cpp \
    control.cpp

win32 {
    INCLUDEPATH += "C:\SDL-1.2.15\include" \

    LIBS += -L"C:\SDL-1.2.15\lib" \
            -lSDL \
            -lSDLmain \
            -lSDL_image \
            -llibgfxdll
}

DEFINES += _WIN32 WIN32
TEMPLATE = app

HEADERS += \
    app.h \
    sprite.h \
    entity.h \
    timer.h \
    text.h \
    e_tower.h \
    e_enemy.h \
    animation.h \
    resources.h \
    map.h \
    sound.h \
    e_ground.h \
    camera.h \
    control.h
