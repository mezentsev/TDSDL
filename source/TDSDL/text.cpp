#include "text.h"

Text::Text(QString text, QString font, int size, int style, int x, int y, int r, int g, int b, int a, int w = 0)
{
    this->text = text;
    this->path = font;
    this->size = size;
    this->style = style;
    this->x = x;
    this->y = y;
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
    this->w = w;

    this->font = TTF_OpenFont(font.toAscii().data(), size);
    if (!this->font)
        this->font = NULL;

    switch (style)
    {
        case 0: TTF_SetFontStyle( this->font, TTF_STYLE_NORMAL );break;
        case 1: TTF_SetFontStyle( this->font, TTF_STYLE_BOLD );break;
        case 2: TTF_SetFontStyle( this->font, TTF_STYLE_ITALIC );break;
        case 3: TTF_SetFontStyle( this->font, TTF_STYLE_UNDERLINE );break;
        case 4: TTF_SetFontStyle( this->font, TTF_STYLE_BOLD | TTF_STYLE_ITALIC);break;
        default:TTF_SetFontStyle( this->font, TTF_STYLE_NORMAL );break;
    }
}

Text::~Text()
{
    if (this->font != NULL)
        delete this->font;
    this->font = NULL;
}


bool Text::refresh(SDL_Surface *dest)
{
    if (this->font == NULL)
        return false;

    SDL_Color color;
    color.b = this->b;
    color.r = this->r;
    color.g = this->g;

    SDL_Rect rect;
    rect.x = this->x;
    rect.y = this->y;

    SDL_Surface *tmp = TTF_RenderUTF8_Solid(this->font, this->text.toAscii().data(), color);
    SDL_BlitSurface(tmp, NULL, dest, &rect);
    SDL_FreeSurface(tmp);

    return true;
}

Text *Text::setXY(int x, int y)
{
    this->x = x;
    this->y = y;
    return this;
}

Text *Text::setSize(int size)
{
    this->size = size;
    return this;
}

Text *Text::setStyle(int style)
{
    this->style = style;
    return this;
}

int Text::getX()
{
    return this->x;
}

int Text::getY()
{
    return this->y;
}

int Text::getSize()
{
    return this->size;
}

void Text::append(QString text)
{
    this->text += text;
}

void Text::setText(QString text)
{
    this->text = text;
}

Text *Text::setColor(int r, int g, int b, int a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
    return this;
}
