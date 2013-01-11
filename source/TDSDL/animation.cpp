#include "animation.h"
#include <QDebug>

Animation::Animation(sf::Sprite * sprite, int cnt, int rate, int type)
{
    this->sprite = sprite;
    this->rect = sprite->GetSubRect();
    this->cnt = cnt;
    this->rate = rate;
    this->type = type;
    this->oldTime = 0;
    this->curFrame = 0;
}

Animation::~Animation()
{
//    if (this->sprite != NULL)
//        delete this->sprite;
//    this->sprite = NULL;
}

int Animation::getCurFrame()
{
    return this->curFrame;
}

void Animation::setCurFrame(int frame)
{
    if (frame >= this->cnt)
        this->curFrame = 0;
    else
        this->curFrame = frame;
}

sf::IntRect Animation::animate(sf::RenderWindow * screen)
{
    this->oldTime += screen->GetFrameTime() * 1000.f;
    if(this->rate > this->oldTime)
    {
        sf::IntRect area;
        area.Left = this->rect.Left;
        area.Top = (this->rect.GetHeight() * this->curFrame) / this->cnt;
        area.Right = this->rect.GetWidth();
        area.Bottom = (this->rect.GetHeight() / this->cnt) + area.Top;
        return area;
    }
    this->oldTime = 0;

    this->setCurFrame(this->getCurFrame() + 1);

    sf::IntRect area;
    area.Left = this->rect.Left;
    area.Top = (this->rect.GetHeight() * this->curFrame) / this->cnt;
    area.Right = this->rect.GetWidth();
    area.Bottom = (this->rect.GetHeight() / this->cnt) + area.Top;

    return area;
}

sf::Sprite *Animation::getSprite()
{
    return this->sprite;
}
