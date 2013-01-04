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
    SDL_Surface* tmp = NULL;

    if((tmp = IMG_Load(path.toAscii().data())) == NULL) {
        return NULL;
    }

    this->sprite = SDL_DisplayFormat(tmp);
    SDL_FreeSurface(tmp);

    return this->sprite;
}

bool Sprite::Draw(SDL_Surface *dest, int x, int y)
{
    if(dest == NULL) {
            return false;
    }

    SDL_Rect area;
    area.x = x;
    area.y = y;

    SDL_BlitSurface(this->sprite, NULL, dest, &area);

    return true;
}
