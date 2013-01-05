#include "animation.h"

Animation::Animation(Sprite * sprite, int w, int h, int cnt, int rate, int type)
{
    this->sprite = sprite;
    this->w = w;
    this->h = h;
    this->cnt = cnt;
    this->rate = rate;
    this->type = type;
}

Animation::~Animation()
{
    if (this->sprite != NULL)
        delete this->sprite;
    this->sprite = NULL;
}
