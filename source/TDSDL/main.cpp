#ifdef _WIN32
#include <cstdio>
#elif linux
#include <stdio.h>
#endif

#include "SDL/SDL.h"
#include <cstdlib>
#include <ctime>

bool done;
SDL_Surface * screen;
SDL_Event event;

#undef main

int main ( int argc, char** argv )
{
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }
    srand(time(NULL));
    atexit(SDL_Quit);
    screen = SDL_SetVideoMode(550, 420, 16, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set video mode: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Flip(screen);
    while (!done)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
            {
                done = true;
                break;
            }
            case SDL_KEYDOWN:
            {
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                    {
                        done = true;
                        break;
                    }
                    case SDLK_b:
                    {
                        break;
                    }
                }
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                if (event.button.button = SDL_BUTTON_LEFT)
                {
                    int x = event.button.x, y = event.button.y;
                    SDL_Flip(screen);
                }
                break;
            }
        }
    }
    printf("Exited cleanly\n");
    return 0;
}
