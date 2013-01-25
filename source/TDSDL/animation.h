#ifndef ANIMATION_H
#define ANIMATION_H

#include "SFML/Graphics.hpp"

class Animation
{
private:
    sf::Sprite sprite;
    sf::IntRect rect;
    int   cnt;  //Количество кадров
    float rate; //Скорость анимации, кадры/сек
    int   type; //Тип анимации
    int curFrame;
    float sumTime;

public:
    Animation(sf::Sprite * sprite, int cnt, int rate, int type);
    Animation(Animation * anim);
    ~Animation();

    // Возвращает номер текущего кадра
    int getCurFrame();
    void setCurFrame(int frame);
    int getFrameHeight();
    int getFrameWidth();

    // Цикл смены кадров
    sf::IntRect animate(sf::Time);
    sf::Sprite * getSprite();
};

#endif // ANIMATION_H
