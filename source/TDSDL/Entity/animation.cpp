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

int Animation::getFrameHeight()
{
    return this->rect.height / this->cnt;
}

int Animation::getFrameWidth()
{
    return this->rect.width;
}

sf::IntRect Animation::animate(sf::Time time)
{
    this->sumTime += time.asSeconds();
    if ((1 / this->rate) > this->sumTime)
    {
        sf::IntRect area;
//        area.left   =  this->rect.left;
//        area.top    = (this->rect.height * this->curFrame) / this->cnt;
//        area.width  =  this->rect.width;
//        area.height = (this->rect.height / this->cnt);
        area.left   = (this->rect.width * this->curFrame) / this->cnt;
        area.top    = this->rect.top;
        area.width  = this->rect.width / this->cnt;
        area.height = this->rect.height;
        return area;
    }

    this->sumTime = this->sumTime - 1 / this->rate;
    this->setCurFrame(this->getCurFrame() + 1);

    sf::IntRect area;
// для сверху вниз
//    area.left   =  this->rect.left;
//    area.top    = (this->rect.height * this->curFrame) / this->cnt;
//    area.width  =  this->rect.width;
//    area.height = (this->rect.height / this->cnt);
// для слева направо
    area.left   = (this->rect.width * this->curFrame) / this->cnt;
    area.top    = this->rect.top;
    area.width  = this->rect.width / this->cnt;
    area.height = this->rect.height;

    return area;
}

sf::Sprite *Animation::getSprite()
{
    return &this->sprite;
}
