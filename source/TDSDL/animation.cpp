#include "animation.h"
#include <QDebug>

Animation::Animation(Sprite * sprite, int cnt, int rate, int type)
{
    this->sprite = sprite;
    this->w = sprite->w;
    this->h = sprite->h;
    this->cnt = cnt;
    this->rate = rate;
    this->type = type;
    this->oldTime = 0;
    this->curFrame = 0;
}

Animation::~Animation()
{
    if (this->sprite != NULL)
        delete this->sprite;
    this->sprite = NULL;
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

SDL_Rect Animation::animate()
{
    if(this->oldTime + this->rate > SDL_GetTicks()) {
        SDL_Rect area;
        area.x = 0;
        area.y = (this->h * this->curFrame / this->cnt);
        area.w = this->w;
        area.h = (this->h / this->cnt);
        return area;
    }

    this->oldTime += this->rate;

    this->setCurFrame(this->getCurFrame() + 1);

    SDL_Rect area;
    area.x = 0;
    area.y = (this->h * this->curFrame) / this->cnt;
    area.w = this->w;
    area.h = (this->h / this->cnt);

    //qDebug() << area.y;
    return area;
}

Sprite *Animation::getSprite()
{
    return this->sprite;
}
