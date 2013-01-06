#include "sprite.h"
#include <QDebug>

Sprite::Sprite()
{
    this->surface = NULL;
    this->w = 0;
    this->h = 0;
}

Sprite::~Sprite()
{
/******************************************************/
    if (this->surface != NULL)
        SDL_FreeSurface(this->surface);
    this->surface = NULL;
/******************************************************/
}

SDL_Surface* Sprite::Load(QString path)
{
    this->path = path;
    SDL_Surface* tmp = NULL;

    if((tmp = IMG_Load(path.toAscii().data())) == NULL) {
        return NULL;
    }

    this->surface = SDL_DisplayFormat(tmp);
    SDL_FreeSurface(tmp);

    this->w = this->surface->w;
    this->h = this->surface->h;

    return this->surface;
}

bool Sprite::Draw(SDL_Surface *dest, SDL_Rect* a, SDL_Rect* b)
{
    if(dest == NULL) {
            return false;
    }

    if (a->x == -1 || a->y == -1)
        SDL_BlitSurface(this->surface, NULL, dest, b);
    else
        SDL_BlitSurface(this->surface, a, dest, b);

    return true;
}
