#ifndef APP_H
#define APP_H

#endif // APP_H

#include <QObject>

class App : public QObject {
private:
    bool running;
    SDL_Surface * screen;
public:
    App();
    int Execute();

    bool Init();
    void Event(SDL_Event* event);
    void Loop();
    void Render();
    void Cleanup();

public slots:
   void setValue(int value);

signals:
   void valueChanged(int newValue);
};
