SOURCES += \
    main.cpp \
    app.cpp

win32 {
    INCLUDEPATH += "C:\SDL-1.2.15\include"

    LIBS += -L"C:\SDL-1.2.15\lib" \
            -lSDL \
            -lSDLmain
}

DEFINES += _WIN32 WIN32
TEMPLATE = app

HEADERS += \
    app.h
