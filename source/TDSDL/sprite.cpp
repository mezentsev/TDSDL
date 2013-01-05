#include "sprite.h"

Sprite::Sprite()
{
    this->surface = NULL;
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

    return this->surface;
}

bool Sprite::Draw(SDL_Surface *dest, int x, int y)
{
    if(dest == NULL) {
            return false;
    }
    SDL_Rect area;
    area.x = x;
    area.y = y;

    SDL_BlitSurface(this->surface, NULL, dest, &area);

    return true;
}
