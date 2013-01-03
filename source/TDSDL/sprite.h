#ifndef SPRITE_H
#define SPRITE_H

#include <QString>
#include "SDL/SDL.h"

class Sprite
{
private:
    SDL_Surface* sprite;
    int x, y;
    QString path;
public:
    Sprite();
    ~Sprite();
    SDL_Surface* Load(QString path);
    bool Draw(SDL_Surface* dest, int x, int y);
};

#endif // SPRITE_H
