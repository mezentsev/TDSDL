#include "animation.h"
#include <QDebug>

Animation::Animation(sf::Sprite * sprite, int cnt, int rate, int type)
{
    this->sprite = *sprite;
    this->rect   = sprite->getTextureRect();
    this->cnt    = cnt;
    this->rate   = rate;
    this->type   = type;

    this->curFrame = 0;
    this->sumTime  = 0;
}

Animation::Animation(Animation *anim)
{
    *this = *anim;
}

Animation::~Animation()
{
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

sf::IntRect Animation::animate(sf::Time time)
{
    this->sumTime += time.asSeconds() * 1000.f;
    if (this->rate > this->sumTime)
    {
        sf::IntRect area;
        area.left   =  this->rect.left;
        area.top    = (this->rect.height * this->curFrame) / this->cnt;
        area.width  =  this->rect.width;
        area.height = (this->rect.height / this->cnt) + area.top;
        return area;
    }
    this->sumTime = this->sumTime - this->rate;

    this->setCurFrame(this->getCurFrame() + 1);

    sf::IntRect area;
    area.left   =  this->rect.left;
    area.top    = (this->rect.height * this->curFrame) / this->cnt;
    area.width  =  this->rect.width;
    area.height = (this->rect.height / this->cnt) + area.top;

    return area;
}

sf::Sprite *Animation::getSprite()
{
    return &this->sprite;
}
