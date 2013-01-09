#ifndef TEXT_H
#define TEXT_H

#include "SDL/SDL_ttf.h"
#include <QString>

class Text
{
private:
    QString text;
    QString path;
    int size;
    int style;
    int x,y;
    int r,g,b,a;
    int w; //ширина, в которую ужать

    TTF_Font *font;
public:
    ~Text();

    Text * setXY(int x, int y);
    Text * setSize(int size);
    Text * setStyle(int style);
    int getX();
    int getY();
    int getSize();
    // дописать
    void append(QString text);
    void setText(QString text);
    Text * setColor(int r, int g, int b, int a);
    Text(QString text, QString font, int size, int style, int x, int y, int r, int g, int b, int a, int w);
    bool refresh(SDL_Surface *dest);
};

#endif // TEXT_H
