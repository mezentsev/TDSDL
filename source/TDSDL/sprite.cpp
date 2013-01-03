#include "sprite.h"

Sprite::Sprite()
{
    this->sprite = NULL;
}

Sprite::~Sprite()
{
    if (this->sprite)
        SDL_FreeSurface(this->sprite);
    this->sprite = NULL;
}

SDL_Surface *Sprite::Load(QString path)
{
    SDL_Surface *tmp = NULL;
    return tmp;
}

bool Sprite::Draw(SDL_Surface *src, SDL_Surface *dest, int x, int y)
{
    return false;
}
