#ifndef TEXT_H
#define TEXT_H

#include "app.h"

// Класс работы с текстом
// Нужна либа SDL_ttf
class Text
{
private:
    QString text;
public:
    Text();
    Text(QString text, int x, int y);
    ~Text();

    void setXY(int x, int y);
    bool draw();
    // дописать
    void append(QString text);
    void setColor(int r, int g, int b, int a);
};

#endif // TEXT_H
