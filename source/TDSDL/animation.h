#ifndef ANIMATION_H
#define ANIMATION_H

#include "sprite.h"

class Animation
{
private:
    Sprite * sprite;
    int w;
    int h;
    int cnt; //Количество кадров
    int rate; //Частота смены
public:
    Animation(Sprite * sprite, int w, int h, int cnt, int rate);
    ~Animation();
};

#endif // ANIMATION_H
