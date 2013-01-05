#include "animation.h"

Animation::Animation(Sprite * sprite, int cnt, int rate, int type)
{
    this->sprite = sprite;
    this->w = sprite->surface->w;
    this->h = sprite->surface->h;
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

Sprite * Animation::animate()
{
    if(this->oldTime + this->rate > SDL_GetTicks()) {
        return;
    }

    this->oldTime = SDL_GetTicks();

    this->setCurFrame(this->getCurFrame() + 1);

    SDL_Rect area;
    area.x = 0;
    area.y = (this->h * this->curFrame / this->cnt);
    area.w = this->w;
    area.h = (this->h / this->cnt);

    SDL_Surface* tmp = NULL;
    SDL_BlitSurface(this->sprite->surface, &area, tmp, NULL);

    return tmp;
}
