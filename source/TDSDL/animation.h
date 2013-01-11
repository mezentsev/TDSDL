#ifndef ANIMATION_H
#define ANIMATION_H

#include "SFML/Graphics.hpp"

class Animation
{
private:
    sf::Sprite * sprite;
    int w;
    int h;
    int cnt; //Количество кадров
    int rate; //Частота смены
    int type; //Тип анимации
    int curFrame;
    int oldTime;
public:
    Animation(sf::Sprite * sprite, int cnt, int rate, int type);
    ~Animation();

    // Возвращает номер текущего кадра
    int getCurFrame();
    void setCurFrame(int frame);

    // Цикл смены кадров
//    SDL_Rect animate();
    sf::Sprite * getSprite();
};

#endif // ANIMATION_H
