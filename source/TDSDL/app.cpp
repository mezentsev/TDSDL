#include "app.h"


/******************************************************/
Entity ent;
/******************************************************/


App::App()
{
    this->running = true;
}

// Инициализация окна и связанных параметров
bool App::Init()
{
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return false;
    }

    this->screen = SDL_SetVideoMode(1920, 1080, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
    if ( !this->screen )
    {
        printf("Unable to set video mode: %s\n", SDL_GetError());
        return false;
    }


/******************************************************/
    Sprite spr;
    spr.Load("C:/abc.png");
    ent.setSprite(&spr);
/******************************************************/


    return true;
}

// Запуск приложения
int App::Execute()
{
    if (this->Init() == false)
    {
        return -1;
    }

    SDL_Event event;

    // Пока запущенно приложение будем считывать события и отрисовывать в цикле
    while (this->running)
    {
        // Ждём события клавиатуры, мыши и т.п.
        SDL_PollEvent(&event);
        this->Event(&event);

        this->Loop();

        // Отрисовка
        this->Render();
    }

    this->Cleanup();
    return 0;
}

// Функция обрабатывает все поступающие события от мышки, клавиатуры, джойстика и других устройств.
void App::Event(SDL_Event* event)
{
    switch (event->type)
    {
        case SDL_QUIT:
        {
            this->running = false;
            break;
        }
        case SDL_KEYDOWN:
        {
            switch (event->key.keysym.sym)
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

            }
            break;
        }
    }
}

// Функция обрабатывает обновление данных, например движение NPC по экрану, уменьшение здоровье персонажа и так далее.
void App::Loop()
{

}



// Функция занимается отображением всего на экране. Она НЕ обрабатывает манипуляции с данными - этим занимается Loop.
void App::Render()
{
/******************************************************/
    ent.setXY(ent.getX()+1,ent.getY()+1);
    ent.refresh(screen);
/******************************************************/
    SDL_Flip(screen);
}

// Функция просто отключает все использующиеся ресурсы и закрывает игру.
void App::Cleanup()
{
    SDL_Quit();
}
