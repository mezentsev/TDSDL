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
    int type; //Тип анимации
    int curFrame;
    int oldTime;
public:
    Animation(Sprite * sprite, int cnt, int rate, int type);
    ~Animation();

    // Возвращает номер текущего кадра
    int getCurFrame();
    void setCurFrame(int frame);

    // Цикл смены кадров
    SDL_Rect* animate();
    Sprite * getSprite();
};

#endif // ANIMATION_H
