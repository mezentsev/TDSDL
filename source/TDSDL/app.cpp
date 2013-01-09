#include "app.h"

#define TICK_INTERVAL    30

quint32 TimeLeft(void)
{
    static quint32 next_time = 0;
    quint32 now;

    now = SDL_GetTicks();
    if ( next_time <= now ) {
        next_time = now+TICK_INTERVAL;
        return(0);
    }
    return(next_time-now);
}

App::App()
{
    this->_sprites  = new Resources<Sprite>();
    this->_entities = new Resources<Entity>();
    this->_anims    = new Resources<Animation>();
    this->_cameras  = new Resources<Camera>();
    this->_maps     = new Resources<Map>();
    this->_texts    = new Resources<Text>();
    this->running   = true;
}

// Инициализация окна и связанных параметров
bool App::Init()
{
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 || TTF_Init () < 0)
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return false;
    }

    SDL_WM_SetCaption("TDSDL", "TDSDL");

    this->screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF );//| SDL_FULLSCREEN);
    if ( !this->screen )
    {
        printf("Unable to set video mode: %s\n", SDL_GetError());
        return false;
    }

    // Выделяем память под спрайт и не забываем выгрузить в деструкторе Entity
    Sprite * spr = new Sprite;
    spr->Load("images/abc.png");
    Sprite * spr_ground1 = new Sprite;
    spr_ground1->Load("images/green.png");
    Sprite * spr_ground2 = new Sprite;
    spr_ground2->Load("images/road.png");
    Sprite * spr_ground3 = new Sprite;
    spr_ground3->Load("images/water.png");

    Sprite * animSpr = new Sprite;
    animSpr->Load("images/abcd.png");
    Animation * anim = new Animation(animSpr, 8, 75, 0);

    // Добавляем спрайт в ресурсы
    this->_sprites->add(spr, "firstWave");
    this->_sprites->add(spr_ground1, "green");
    this->_sprites->add(spr_ground2, "road");
    this->_sprites->add(spr_ground3, "water");
    this->_anims->add(anim, "run");

    e_Enemy *ent = new e_Enemy;
    ent->setSprite(this->_sprites->getRes("firstWave"))->setHW(64,64);
    ent->addAnim(this->_anims->getRes("run"), "run1");
    ent->setAnim("run1")->animate();
    this->_entities->add(ent,"enemy_Dragon");

    //добавляем камеру и выбираем её в качестве главной
    Camera *cam = new Camera;
    _cameras->add(cam,"Cam1");
    mainCamera = cam;

    //считывание карты и создание сущностей земли
    this->readMap("maps/map.txt");

    //вот здесь содержится то, что хорошо бы упаковать в класс e_Ground
    //здесь распределение картинок в зависимости от типа земли
    for (int y=0; y<this->_maps->getRes("Ground")->getHeight(); y++)
    {
        for (int x=0; x<this->_maps->getRes("Ground")->getWidth(); x++)
        {
            e_Ground *ground = new e_Ground;
            switch (this->_maps->getRes("Ground")->getType(x,y))
            {
                case 0:
                {
                    ground->setSprite(this->_sprites->getRes("water"));
                    break;
                }
                case 1:
                {
                    ground->setSprite(this->_sprites->getRes("road"));
                    break;
                }
                case 2:
                {
                    ground->setSprite(this->_sprites->getRes("green"));
                    break;
                }
            }
            ground->setXY(x*60,y*60)->setHW(60,60);
            this->_entities->add(ground,QString::number(x)+","+QString::number(y));
            ground = NULL;
        }
    }

    this->control.setCamera(this->mainCamera);

    Text *text = new Text("Дракоша", "font/univers.ttf", 25, 0, -50, -25, 255, 0, 0, 0, 0);
    this->_texts->add(text, "text_drakoXY");

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
        while (SDL_PollEvent(&event))
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
        case SDLK_RIGHT:
        {
            this->control.cameraRight(true);
            break;
        }
        case SDLK_LEFT:
        {
            this->control.cameraLeft(true);
            break;
        }
        case SDLK_DOWN:
        {
            this->control.cameraDown(true);
            break;
        }
        case SDLK_UP:
        {
            this->control.cameraUp(true);
            break;
        }
        case SDLK_b:
        {
            break;
        }
        }
        break;
    }
    case SDL_KEYUP:
    {
        switch (event->key.keysym.sym)
        {
        case SDLK_RIGHT:
        {
            this->control.cameraRight(false);
            break;
        }
        case SDLK_LEFT:
        {
            this->control.cameraLeft(false);
            break;
        }
        case SDLK_DOWN:
        {
            this->control.cameraDown(false);
            break;
        }
        case SDLK_UP:
        {
            this->control.cameraUp(false);
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
    quint32 left = TimeLeft();
    int x = _entities->getRes("enemy_Dragon")->getX() + left / 28;
    int y = _entities->getRes("enemy_Dragon")->getY() + left / 28;
    this->_entities->getRes("enemy_Dragon")->setXY(x,y);
    this->_texts->getRes("text_drakoXY")->setXY(x-30,y-50)->setText("x: "+QString::number(x)+", y: "+QString::number(y));
    control.events();
}

// Функция занимается отображением всего на экране. Она НЕ обрабатывает манипуляции с данными - этим занимается Loop.
void App::Render()
{
    // Заливка фона
    SDL_FillRect(this->screen, &this->screen->clip_rect, SDL_MapRGB(this->screen->format, 0, 0, 0));

    // Выведем все ресурсы из Entity
    QMap<QString, Entity*>::iterator i;
    for (i = _entities->getBegin(); i != _entities->getEnd(); ++i)
    {
        if (((*i)->getX() + (*i)->getW() - this->mainCamera->getX() >= 0) && ((*i)->getY() + (*i)->getH() - this->mainCamera->getY() >= 0)
                && ((*i)->getX() - this->mainCamera->getX() <= this->screen->w) && ((*i)->getY() - this->mainCamera->getY() <= this->screen->h))
        {
            (*i)->setXY((*i)->getX() - this->mainCamera->getX(), (*i)->getY() - this->mainCamera->getY());
            (*i)->refresh(this->screen);
            (*i)->setXY((*i)->getX() + this->mainCamera->getX(), (*i)->getY() + this->mainCamera->getY());
        }
        //printf("%s",(*i)->get_name());
    }

    // Выведем все ресурсы из Text
    QMap<QString, Text*>::iterator t;
    for (t = _texts->getBegin(); t != _texts->getEnd(); ++t)
    {
        if (((*t)->getX() - this->mainCamera->getX() >= 0) && ((*t)->getY() + (*t)->getSize() - this->mainCamera->getY() >= 0)
                && ((*t)->getX() - this->mainCamera->getX() <= this->screen->w) && ((*t)->getY() - this->mainCamera->getY() <= this->screen->h))
        {
            (*t)->setXY((*t)->getX() - this->mainCamera->getX(), (*t)->getY() - this->mainCamera->getY());
            (*t)->refresh(this->screen);
            (*t)->setXY((*t)->getX() + this->mainCamera->getX(), (*t)->getY() + this->mainCamera->getY());
        }
        //printf("%s",(*i)->get_name());
    }
    // Обновление экрана
    SDL_Flip(this->screen);
}

// Функция просто отключает все использующиеся ресурсы и закрывает игру.
void App::Cleanup()
{
    delete this->_sprites;
    delete this->_anims;
    delete this->_entities;
    delete this->_maps;
    delete this->_cameras;
    delete this->_texts;

    SDL_Quit();
}

void App::readMap(QString path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
    {
        printf("Unable to open file\n");
        return;
    }
    QTextStream in(&file);
    // а вот то, что в комментах, нужно будет для бинарников
    //QDataStream in(&file);
    //in.setVersion(QDataStream::Qt_4_3);

    int width, height;
    in >> width;
    in >> height;

    // Инициализация карт и добавление их в ресурсы
    Map *map1 = new Map(width,height);
    Map *map2 = new Map(width,height);
    Map *map3 = new Map(width,height);

    this->_maps->add(map1,"Ground");
    this->_maps->add(map2,"Enemy");
    this->_maps->add(map3,"Tower");

    int type;    
    for (int y=0; y<height; y++)
    {
        for (int x=0; x<width; x++)
        {
            in >> type;
            map1->setCell(x,y,type);
        }
    }
}
