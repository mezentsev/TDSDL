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
    this->_sprites = new Resources<Sprite>();
    this->_entity  = new Resources<Entity>();
    this->_anims   = new Resources<Animation>();
    this->_enemies = new Resources<e_Enemy>();
    this->_towers  = new Resources<e_Tower>();
    this->_grounds = new Resources<e_Ground>();
    this->running  = true;
}

// Инициализация окна и связанных параметров
bool App::Init()
{
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
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
    ent->setSprite(this->_sprites->getRes("firstWave"));
    ent->addAnim(this->_anims->getRes("run"), "run1");
    ent->setAnim("run1")->animate();
    this->_enemies->add(ent,"dragon");

    //считывание карты и создание сущностей земли
    this->readMap("maps/map.txt");
    e_Ground *ground = new e_Ground[this->map->getWidth()*this->map->getHeight()];

    //вот здесь содержится то, что хорошо бы упаковать в класс e_Ground
    //здесь распределение картинок в зависимости от типа земли
    for (int y=0; y<this->map->getHeight(); y++)
    {
        for (int x=0; x<this->map->getWidth(); x++)
        {
            switch (this->map->getType(x,y))
            {
                case 0:
                {
                    ground[y*this->map->getWidth()+x].setSprite(this->_sprites->getRes("water"));
                    break;
                }
                case 1:
                {
                    ground[y*this->map->getWidth()+x].setSprite(this->_sprites->getRes("road"));
                    break;
                }
                case 2:
                {
                    ground[y*this->map->getWidth()+x].setSprite(this->_sprites->getRes("green"));
                    break;
                }
            }
            ground[y*this->map->getWidth()+x].setXY(x*60,y*60);
            _grounds->add(&ground[y*this->map->getWidth()+x],QString::number(x)+","+QString::number(y));
        }
    }

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
    // Заливка фона
    SDL_FillRect(this->screen, &this->screen->clip_rect, SDL_MapRGB(this->screen->format, 0, 0, 0));

    quint32 left = TimeLeft();

    for (int y=0; y<this->map->getHeight(); y++)
        for (int x=0; x<this->map->getWidth(); x++)
        {
            _grounds->getRes(QString::number(x)+","+QString::number(y))->refresh(this->screen);
        }

    //
    //e_Enemy *ent = _enemies->getRes("dragon");
    //
    // Выведем все ресурсы из Enemies
    QMap<QString, e_Enemy*>::iterator i;
    for (i = _enemies->getBegin(); i != _enemies->getEnd(); ++i)
    {
        (*i)->setXY((*i)->getX() + left / 28, (*i)->getY() + left / 28);
        (*i)->refresh(this->screen);
    }

    SDL_Flip(this->screen);
}

// Функция просто отключает все использующиеся ресурсы и закрывает игру.
void App::Cleanup()
{
    delete this->_sprites;
    delete this->_anims;
    delete this->_enemies;
    delete this->_towers;
    delete this->_grounds;
    delete this->map;
    delete this->_entity;
    SDL_Quit();
}

void App::readMap(QString path)
{
    // TODO: Изменить код на кроссплатформенный (например Qt'шными средствами)
    FILE *file;
    file = fopen(path.toStdString().c_str(),"r");

    int width, height;
    fscanf(file,"%d",&width);
    fscanf(file,"%d",&height);
    this->map = new Map(width,height);

    int type;
    for (int y=0; y<height; y++)
    {
        for (int x=0; x<width; x++)
        {
            fscanf(file,"%d",&type);
            this->map->setCell(x,y,type);
        }
    }

    fclose(file);
}
