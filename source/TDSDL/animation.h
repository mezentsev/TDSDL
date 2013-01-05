#ifndef ANIMATION_H
#define ANIMATION_H

#include "app.h"

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
public:
    Animation(Sprite * sprite, int w, int h, int cnt, int rate, int type);
    ~Animation();

    // Возвращает номер текущего кадра
    int getCurFrame();
    void setCurFrame(int frame);

    // Цикл смены кадров
    void animate();
};

#endif // ANIMATION_H
