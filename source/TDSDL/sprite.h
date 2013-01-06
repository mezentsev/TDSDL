#ifndef SPRITE_H
#define SPRITE_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <QString>

class Sprite
{
private:
    SDL_Surface* surface;
    int x, y;
    QString path;
public:
    int w, h;
    Sprite();
    ~Sprite();
    SDL_Surface* Load(QString path);
    bool Draw(SDL_Surface* dest, SDL_Rect* a, SDL_Rect* b);
};

#endif // SPRITE_H
