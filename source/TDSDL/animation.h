#ifndef ANIMATION_H
#define ANIMATION_H

#include "SFML/Graphics.hpp"

class Animation
{
private:
    sf::Sprite * sprite;
    sf::IntRect rect;
    int cnt; //Количество кадров
    int rate; //Частота смены
    int type; //Тип анимации
    int curFrame;
    float sumTime;

public:
    Animation(sf::Sprite * sprite, int cnt, int rate, int type);
    ~Animation();

    // Возвращает номер текущего кадра
    int getCurFrame();
    void setCurFrame(int frame);

    // Цикл смены кадров
    sf::IntRect animate(sf::RenderWindow * screen);
    sf::Sprite * getSprite();
};

#endif // ANIMATION_H
