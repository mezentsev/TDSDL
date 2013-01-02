#ifdef _WIN32
#include <cstdio>
#elif linux
#include <stdio.h>
#endif

#include "SDL/SDL.h"
#include <cstdlib>
#include <ctime>

#include "main.h"

bool done;

#undef main

App::App(){
    this->running = true;
}

// Инициализация окна и связанных параметров
bool App::Init(){
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return false;
    }

    this->screen = SDL_SetVideoMode(550, 420, 16, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if ( !this->screen )
    {
        printf("Unable to set video mode: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

// Запуск приложения
int App::Execute(){
    if(Init() == false) {
        return -1;
    }

    SDL_Event event;

    // Пока запущенно приложение будем считывать события и отрисовывать в цикле
    while(this->running) {
        // Ждём события клавиатуры, мыши и т.п.
        SDL_WaitEvent(&event);
        this->Event(&event);

        this->Loop();

        // Отрисовка
        this->Render();
    }

    this->Cleanup();
    return 0;
}

// Обработчик событий
void App::Event(SDL_Event* event){
    switch(event->type)
    {
        case SDL_QUIT:
        {
            this->running = false;
            break;
        }
        case SDL_KEYDOWN:
        {
            switch(event->key.keysym.sym)
            {
                case SDLK_ESCAPE:
                {
                    this->running = false;
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
            if (event->button.button = SDL_BUTTON_LEFT)
            {
                int x = event->button.x, y = event->button.y;
                SDL_Flip(screen);
            }
            break;
        }
    }
}

void App::Loop() {}
void App::Render() {}

// Очистка
void App::Cleanup() {
    SDL_Quit();
}

int main ()
{
    App App;
    return App.Execute();
}
