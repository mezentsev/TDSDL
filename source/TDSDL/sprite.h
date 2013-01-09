#ifndef SPRITE_H
#define SPRITE_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <QString>
#include "SDL/SDL_rotozoom.h"

class Sprite
{
private:
    SDL_Surface* surface;
    int w, h;
    QString path;

public:
    Sprite();
    ~Sprite();
    SDL_Surface* Load(QString path);
    bool Draw(SDL_Surface* dest, SDL_Rect* a, SDL_Rect* b, double angle, double scale);
    int getW();
    int getH();
};

#endif // SPRITE_H
