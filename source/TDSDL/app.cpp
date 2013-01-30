﻿#include "app.h"

App::App()
{
    this->screen = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "SFML window", sf::Style::Close, sf::ContextSettings(0,0,8));
    this->screen->setFramerateLimit(60); // Ограничение для правильной работы физ.движка
    this->screen->setVerticalSyncEnabled(true);

    this->control = new Control;
    connect(this->control, SIGNAL(end()), this, SLOT(Close()));

    this->_textures   = new Resources<sf::Texture>();
    this->_sprites    = new Resources<sf::Sprite>();
    this->_entities   = new Resources<Entity>();
    this->_anims      = new Resources<Animation>();
    this->_cameras    = new Resources<sf::View>();

    this->world = new b2World(b2Vec2(0.f, 9.8f));

    this->SCALE = 30.f;
}

bool App::Load()
{
    /**********************  Загрузка изображений ************************/
    sf::Texture *image = new sf::Texture();
    if (!image->loadFromFile("images/dragon_runLeft.png")) return false;
    image->setSmooth(true);
    image->setRepeated(true);
    _textures->add(image,"dragon_runLeft");

    image = new sf::Texture();
    if (!image->loadFromFile("images/dragon_runRight.png")) return false;
    image->setSmooth(true);
    image->setRepeated(true);
    _textures->add(image,"dragon_runRight");

    image = new sf::Texture();
    if (!image->loadFromFile("images/dragon_stayLeft.png")) return false;
    image->setSmooth(true);
    image->setRepeated(true);
    _textures->add(image,"dragon_stayLeft");

    image = new sf::Texture();
    if (!image->loadFromFile("images/dragon_stayRight.png")) return false;
    image->setSmooth(true);
    image->setRepeated(true);
    _textures->add(image,"dragon_stayRight");

    image = new sf::Texture();
    if (!image->loadFromFile("images/dragon_jumpLeft.png")) return false;
    image->setSmooth(true);
    image->setRepeated(true);
    _textures->add(image,"dragon_jumpLeft");

    image = new sf::Texture();
    if (!image->loadFromFile("images/dragon_jumpRight.png")) return false;
    image->setSmooth(true);
    image->setRepeated(true);
    _textures->add(image,"dragon_jumpRight");

    image = new sf::Texture();
    if (!image->loadFromFile("images/dragon_fallLeft.png")) return false;
    image->setSmooth(true);
    image->setRepeated(true);
    _textures->add(image,"dragon_fallLeft");

    image = new sf::Texture();
    if (!image->loadFromFile("images/dragon_fallRight.png")) return false;
    image->setSmooth(true);
    image->setRepeated(true);
    _textures->add(image,"dragon_fallRight");

    image = new sf::Texture();
    if (!image->loadFromFile("images/road.png")) return false;
    image->setSmooth(true);
    image->setRepeated(true);
    _textures->add(image,"road");
    /*********************************************************************/


    /***************  Установка изображений справйтам  *******************/
    sf::Sprite *spr = new sf::Sprite(*_textures->getRes("dragon_runLeft"));
    this->_sprites->add(spr, "dragon_runLeft");

    spr = new sf::Sprite(*_textures->getRes("dragon_runRight"));
    this->_sprites->add(spr, "dragon_runRight");

    spr = new sf::Sprite(*_textures->getRes("dragon_stayLeft"));
    this->_sprites->add(spr, "dragon_stayLeft");

    spr = new sf::Sprite(*_textures->getRes("dragon_stayRight"));
    this->_sprites->add(spr, "dragon_stayRight");

    spr = new sf::Sprite(*_textures->getRes("dragon_jumpLeft"));
    this->_sprites->add(spr, "dragon_jumpLeft");

    spr = new sf::Sprite(*_textures->getRes("dragon_jumpRight"));
    this->_sprites->add(spr, "dragon_jumpRight");

    spr = new sf::Sprite(*_textures->getRes("dragon_fallLeft"));
    this->_sprites->add(spr, "dragon_fallLeft");

    spr = new sf::Sprite(*_textures->getRes("dragon_fallRight"));
    this->_sprites->add(spr, "dragon_fallRight");

    spr = new sf::Sprite(*_textures->getRes("road"));
    this->_sprites->add(spr, "road");
    /*********************************************************************/


    /***************  Создание анимаций из спрайта  **********************/
    Animation * anim = new Animation(this->_sprites->getRes("dragon_runLeft"), 8, 8, 0);
    this->_anims->add(anim, "dragon_runLeft");

    anim = new Animation(this->_sprites->getRes("dragon_runRight"), 8, 8, 0);
    this->_anims->add(anim, "dragon_runRight");

    anim = new Animation(this->_sprites->getRes("dragon_stayLeft"), 1, 1, 0);
    this->_anims->add(anim, "dragon_stayLeft");

    anim = new Animation(this->_sprites->getRes("dragon_stayRight"), 1, 1, 0);
    this->_anims->add(anim, "dragon_stayRight");

    anim = new Animation(this->_sprites->getRes("dragon_jumpLeft"), 1, 1, 0);
    this->_anims->add(anim, "dragon_jumpLeft");

    anim = new Animation(this->_sprites->getRes("dragon_jumpRight"), 1, 1, 0);
    this->_anims->add(anim, "dragon_jumpRight");

    anim = new Animation(this->_sprites->getRes("dragon_fallLeft"), 1, 1, 0);
    this->_anims->add(anim, "dragon_fallLeft");

    anim = new Animation(this->_sprites->getRes("dragon_fallRight"), 1, 1, 0);
    this->_anims->add(anim, "dragon_fallRight");

    anim = new Animation(this->_sprites->getRes("road"), 1, 1, 0);
    this->_anims->add(anim, "road");
    /*********************************************************************/

    return true;
}

// Инициализация окна и связанных параметров
bool App::Init()
{
    sf::View *camera = new sf::View();
    this->mainCamera = camera;
    camera->setSize(this->screen->getSize().x, this->screen->getSize().y);
    camera->setCenter(0,0);
    this->_cameras->add(camera, "default");

    if (!this->Load()) return 0;

    sf::ConvexShape polygon_Player(4);
    polygon_Player.setPoint(0, sf::Vector2f(0,0));
    polygon_Player.setPoint(1, sf::Vector2f(64,0));
    polygon_Player.setPoint(2, sf::Vector2f(64,64));
    polygon_Player.setPoint(3, sf::Vector2f(0,64));

    sf::ConvexShape polygon_PlayerPhys(4);
    polygon_PlayerPhys.setPoint(0, sf::Vector2f(0,0));
    polygon_PlayerPhys.setPoint(1, sf::Vector2f(64,0));
    polygon_PlayerPhys.setPoint(2, sf::Vector2f(64,64));
    polygon_PlayerPhys.setPoint(3, sf::Vector2f(0,64));

    sf::ConvexShape polygon_Ground(4);
    polygon_Ground.setPoint(0, sf::Vector2f(0,0));
    polygon_Ground.setPoint(1, sf::Vector2f(100,0));
    polygon_Ground.setPoint(2, sf::Vector2f(100,64));
    polygon_Ground.setPoint(3, sf::Vector2f(0,64));

    sf::ConvexShape polygon_GroundPhys(4);
    polygon_GroundPhys.setPoint(0, sf::Vector2f(0,25));
    polygon_GroundPhys.setPoint(1, sf::Vector2f(100,25));
    polygon_GroundPhys.setPoint(2, sf::Vector2f(100,64));
    polygon_GroundPhys.setPoint(3, sf::Vector2f(0,64));

    QList<sf::ConvexShape> polygon_PlayerPhysList;
    polygon_PlayerPhysList.append(polygon_PlayerPhys);

    QList<sf::ConvexShape> polygon_GroundPhysList;
    polygon_GroundPhysList.append(polygon_GroundPhys);

    /***************  Создание игрока, назначение стандартной анимации ********************/
    Unit *ent = new Unit(this->_anims->getRes("dragon_stayRight"), 0, 0, polygon_Player, polygon_PlayerPhysList, this->world, Physics::DYNAMIC, this->SCALE);
    ent->addAnim(this->_anims->getRes("dragon_runRight"), "runRight");
    ent->addAnim(this->_anims->getRes("dragon_runLeft"), "runLeft");
    ent->addAnim(this->_anims->getRes("dragon_stayLeft"), "stayLeft");
    ent->addAnim(this->_anims->getRes("dragon_stayRight"), "stayRight");
    ent->addAnim(this->_anims->getRes("dragon_jumpLeft"), "jumpLeft");
    ent->addAnim(this->_anims->getRes("dragon_jumpRight"), "jumpRight");
    ent->addAnim(this->_anims->getRes("dragon_fallLeft"), "fallLeft");
    ent->addAnim(this->_anims->getRes("dragon_fallRight"), "fallRight");
    this->_entities->add(ent,"player");
    /**************************************************************************************/

    /***************  Создание окружения, назначение стандартной анимации ********************/
    Entity *ents = NULL;

    ents = new Entity(this->_anims->getRes("road"), 0,180, polygon_Ground, polygon_GroundPhysList, this->world, Physics::STATIC, this->SCALE);
    this->_entities->add(ents,"dnishe1");

    ents = new Entity(this->_anims->getRes("road"), -380,200, polygon_Ground, polygon_GroundPhysList, this->world, Physics::STATIC, this->SCALE);
    this->_entities->add(ents,"dnishe2");

    ents = new Entity(this->_anims->getRes("road"), 180,220, polygon_Ground, polygon_GroundPhysList, this->world, Physics::STATIC, this->SCALE);
    this->_entities->add(ents,"dnishe3");
    /*********************************************************************/

    connect(this->control, SIGNAL(setEntControl(Unit::ORDER)), this->_entities->getRes("player"), SLOT(setControl(Unit::ORDER)));
    connect(this->control, SIGNAL(createGround(int,int)), this, SLOT(createGround(int,int)));

/*
    //считывание карты и создание сущностей земли
    this->readMap("maps/map.txt");

    this->control.setCamera(this->mainCamera);
*/
    return true;
}

// Запуск приложения
int App::Execute()
{
    if (!this->Init())
    {
        printf("Error while init window");
        return -1;
    }

    sf::Event event;
    while (this->screen->isOpen())
    {
        this->world->Step(freq.asSeconds(), 8, 8);

        this->freq = clock.getElapsedTime();

        clock.restart();

        this->screen->clear();

        while (this->screen->pollEvent(event))
        {
            this->Event(&event);
        }

        this->Loop();

        this->Render();        
    }

    this->Cleanup();
    return 0;
}

// Функция обрабатывает все поступающие события от мышки, клавиатуры, джойстика и других устройств.
void App::Event(sf::Event *event)
{
    control->doControl(event);
}

// Функция обрабатывает обновление данных, например движение NPC по экрану, уменьшение здоровье персонажа и так далее.
void App::Loop()
{
    QMap<QString, Entity*>::iterator i;
    for (i = _entities->getBegin(); i != _entities->getEnd(); ++i)
    {
        (*i)->doPhysics(this->SCALE);
    }

    mainCamera->setCenter(_entities->getRes("player")->getX(),_entities->getRes("player")->getY());
}

// Функция занимается отображением всего на экране. Она НЕ обрабатывает манипуляции с данными - этим занимается Loop.
void App::Render()
{
    this->screen->setView(*mainCamera);

    QMap<QString, Entity*>::iterator i;
    for (i = _entities->getBegin(); i != _entities->getEnd(); ++i)
    {
        this->screen->draw((*i)->animate(this->freq));
    }

    this->screen->display();
}

// Функция просто отключает все использующиеся ресурсы и закрывает игру.
void App::Cleanup()
{
    delete this->screen;
    delete this->_sprites;
    delete this->_textures;
    delete this->_anims;
    delete this->_entities;
    delete this->_cameras;
    delete this->world;
}

void App::createGround(int x, int y)
{
    int newX = x + this->mainCamera->getCenter().x-this->mainCamera->getSize().x/2;
    int newY = y + this->mainCamera->getCenter().y-this->mainCamera->getSize().y/2;

//    Entity * ent = new Entity(this->_anims->getRes("road"), newX, newY, 100, 64, this->world, Physics::DYNAMIC, this->SCALE);
//    this->_entities->add(ent, "dnishe"+this->_entities->size());
}
void App::Close()
{
    this->screen->close();
}

//void App::readMap(QString path)
//{
//    QFile file(path);
//    if (!file.open(QIODevice::ReadOnly))
//    {
//        printf("Unable to open file\n");
//        return;
//    }
//    QTextStream in(&file);
//    // а вот то, что в комментах, нужно будет для бинарников
//    //QDataStream in(&file);
//    //in.setVersion(QDataStream::Qt_4_3);

//    int width, height;
//    in >> width;
//    in >> height;

//    // Инициализация карт и добавление их в ресурсы
//    Map *map1 = new Map(width,height);
//    Map *map2 = new Map(width,height);
//    Map *map3 = new Map(width,height);

//    this->_maps->add(map1,"Ground");
//    this->_maps->add(map2,"Enemy");
//    this->_maps->add(map3,"Tower");

//    int type;
//    for (int y=0; y<height; y++)
//    {
//        for (int x=0; x<width; x++)
//        {
//            in >> type;
//            map1->setCell(x,y,type);
//        }
//    }
//}
