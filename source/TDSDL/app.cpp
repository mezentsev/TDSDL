#include "app.h"

App::App()
{
    this->screen = new sf::RenderWindow(sf::VideoMode(1000, 800, 32), "SFML window", sf::Style::Close, sf::ContextSettings(0,0,8));
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
    this->resPath = "resource.tdsdl";

    this->levels();
}

bool App::Load()
{
    /**********************  Загрузка изображений ************************/
    sf::Texture *image = new sf::Texture();
    if (!image->loadFromFile("images/units/main_hero/hero_runLeft.png")) return false;
    image->setSmooth(true);
    image->setRepeated(true);
    _textures->add(image,"dragon_runLeft");

    image = new sf::Texture();
    if (!image->loadFromFile("images/units/main_hero/hero_runRight.png")) return false;
    image->setSmooth(true);
    image->setRepeated(true);
    _textures->add(image,"dragon_runRight");

    image = new sf::Texture();
    if (!image->loadFromFile("images/units/main_hero/hero_stayLeft.png")) return false;
    image->setSmooth(true);
    image->setRepeated(true);
    _textures->add(image,"dragon_stayLeft");

    image = new sf::Texture();
    if (!image->loadFromFile("images/units/main_hero/hero_stayRight.png")) return false;
    image->setSmooth(true);
    image->setRepeated(true);
    _textures->add(image,"dragon_stayRight");

    image = new sf::Texture();
    if (!image->loadFromFile("images/units/main_hero/hero_jumpLeft.png")) return false;
    image->setSmooth(true);
    image->setRepeated(true);
    _textures->add(image,"dragon_jumpLeft");

    image = new sf::Texture();
    if (!image->loadFromFile("images/units/main_hero/hero_jumpRight.png")) return false;
    image->setSmooth(true);
    image->setRepeated(true);
    _textures->add(image,"dragon_jumpRight");

    image = new sf::Texture();
    if (!image->loadFromFile("images/units/main_hero/dragon_fallLeft.png")) return false;
    image->setSmooth(true);
    image->setRepeated(true);
    _textures->add(image,"dragon_fallLeft");

    image = new sf::Texture();
    if (!image->loadFromFile("images/units/main_hero/dragon_fallRight.png")) return false;
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
    Animation * anim = new Animation(this->_sprites->getRes("dragon_runLeft"), 6, 9, 0);
    this->_anims->add(anim, "dragon_runLeft");

    anim = new Animation(this->_sprites->getRes("dragon_runRight"), 6, 9, 0);
    this->_anims->add(anim, "dragon_runRight");

    anim = new Animation(this->_sprites->getRes("dragon_stayLeft"), 5, 7, 0);
    this->_anims->add(anim, "dragon_stayLeft");

    anim = new Animation(this->_sprites->getRes("dragon_stayRight"), 5, 7, 0);
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
    polygon_Player.setPoint(1, sf::Vector2f(170,0));
    polygon_Player.setPoint(2, sf::Vector2f(170,128));
    polygon_Player.setPoint(3, sf::Vector2f(0,128));

    sf::ConvexShape polygon_PlayerPhys(4);
    polygon_PlayerPhys.setPoint(0, sf::Vector2f(40,10));
    polygon_PlayerPhys.setPoint(1, sf::Vector2f(120,10));
    polygon_PlayerPhys.setPoint(2, sf::Vector2f(120,110));
    polygon_PlayerPhys.setPoint(3, sf::Vector2f(40,110));

    sf::ConvexShape polygon_PlayerPhys2(4);
    polygon_PlayerPhys2.setPoint(0, sf::Vector2f(40,110));
    polygon_PlayerPhys2.setPoint(1, sf::Vector2f(120,110));
    polygon_PlayerPhys2.setPoint(2, sf::Vector2f(90,128));
    polygon_PlayerPhys2.setPoint(3, sf::Vector2f(70,128));

    QList<sf::ConvexShape> polygon_PlayerPhysList;
    polygon_PlayerPhysList.append(polygon_PlayerPhys);
    polygon_PlayerPhysList.append(polygon_PlayerPhys2);

    sf::ConvexShape polygon_Ground(4);
    polygon_Ground.setPoint(0, sf::Vector2f(0,0));
    polygon_Ground.setPoint(1, sf::Vector2f(44,24));
    polygon_Ground.setPoint(2, sf::Vector2f(44,64));
    polygon_Ground.setPoint(3, sf::Vector2f(0,64));

    sf::ConvexShape polygon_GroundPhys(4);
    polygon_GroundPhys.setPoint(0, sf::Vector2f(0,10));
    polygon_GroundPhys.setPoint(1, sf::Vector2f(44,34));
    polygon_GroundPhys.setPoint(2, sf::Vector2f(44,40));
    polygon_GroundPhys.setPoint(3, sf::Vector2f(4,40));



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

    ents = new Entity(this->_anims->getRes("road"), 0,190, polygon_Ground, polygon_GroundPhysList, this->world, Physics::STATIC, this->SCALE);
    this->_entities->add(ents,"dnishe1");

    ents = new Entity(this->_anims->getRes("road"), 64,190, polygon_Ground, polygon_GroundPhysList, this->world, Physics::STATIC, this->SCALE);
    this->_entities->add(ents,"dnishe2");

    ents = new Entity(this->_anims->getRes("road"), 128,200, polygon_Ground, polygon_GroundPhysList, this->world, Physics::STATIC, this->SCALE);
    this->_entities->add(ents,"dnishe3");

    ents = new Entity(this->_anims->getRes("road"), 192,210, polygon_Ground, polygon_GroundPhysList, this->world, Physics::STATIC, this->SCALE);
    this->_entities->add(ents,"dnishe4");

    ents = new Entity(this->_anims->getRes("road"), 256,220, polygon_Ground, polygon_GroundPhysList, this->world, Physics::STATIC, this->SCALE);
    this->_entities->add(ents,"dnishe5");

    ents = new Entity(this->_anims->getRes("road"), 320,230, polygon_Ground, polygon_GroundPhysList, this->world, Physics::STATIC, this->SCALE);
    this->_entities->add(ents,"dnishe6");

    ents = new Entity(this->_anims->getRes("road"), 384,240, polygon_Ground, polygon_GroundPhysList, this->world, Physics::STATIC, this->SCALE);
    this->_entities->add(ents,"dnishe7");

    ents = new Entity(this->_anims->getRes("road"), -380,0, polygon_Ground, polygon_GroundPhysList, this->world, Physics::STATIC, this->SCALE);
    this->_entities->add(ents,"dnishe8");
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

bool App::saveRes(QByteArray &arr)
{
    QFile file(this->resPath);
    if (!file.open(QIODevice::WriteOnly))
    {
        printf("Unable to open file\n");
        return false;
    }
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_8); //  явно указываем версию Qt, для сериализации;

    // сохранение данных
    out << arr;

    bool isFlush = file.flush();
    file.close();
    return isFlush;
}

QByteArray App::loadRes()
{
    QByteArray arr;
    QFile file(this->resPath);
    if (!file.open(QIODevice::ReadOnly))
    {
        printf("Unable to open file\n");
        return false;
    }
    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_4_8); //  явно указываем версию Qt, для сериализации;

    // сохранение данных
    in >> arr;

    file.close();
    return arr;
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

void App::levels()
{
    //////////// Сохранение в файл уровней /////////
    QByteArray arr;
    int nul = 0;
    arr.append(1); // Количество уровней
    arr.append(1); // Начало первого уровня

    arr.append(9); // 9 картинок на уровне
        arr.append("images/units/main_hero/hero_runLeft.png");
            arr.append("dragon_runLeft"); // название к текстуре, спрайту, анимации
            arr.append(6); // Количество кадров
            arr.append(9); // Частота
            arr.append(nul); // Тип
        arr.append("images/units/main_hero/hero_runRight.png");
            arr.append("dragon_runRight");
            arr.append(6); // Количество кадров
            arr.append(9); // Частота
            arr.append(nul); // Тип
        arr.append("images/units/main_hero/hero_stayLeft.png");
            arr.append("dragon_stayLeft");
            arr.append(5); // Количество кадров
            arr.append(7); // Частота
            arr.append(nul); // Тип
        arr.append("images/units/main_hero/hero_jumpLeft.png");
            arr.append("dragon_stayRight");
            arr.append(5); // Количество кадров
            arr.append(7); // Частота
            arr.append(nul); // Тип
        arr.append("images/units/main_hero/hero_jumpRight.png");
            arr.append("dragon_jumpLeft");
            arr.append(1); // Количество кадров
            arr.append(1); // Частота
            arr.append(nul); // Тип
        arr.append("images/units/main_hero/hero_stayRight.png");
            arr.append("dragon_jumpRight");
            arr.append(1); // Количество кадров
            arr.append(1); // Частота
            arr.append(nul); // Тип
        arr.append("images/units/main_hero/dragon_fallLeft.png");
            arr.append("dragon_fallLeft");
            arr.append(1); // Количество кадров
            arr.append(1); // Частота
            arr.append(nul); // Тип
        arr.append("images/units/main_hero/dragon_fallRight.png");
            arr.append("dragon_fallRight");
            arr.append(1); // Количество кадров
            arr.append(1); // Частота
            arr.append(nul); // Тип
        arr.append("images/road.png");
            arr.append("road");
            arr.append(1); // Количество кадров
            arr.append(1); // Частота
            arr.append(nul); // Тип

        arr.append(1); // 1 юнит на уровне
        ////////////////////////////////////////////////////
            arr.append("dragon_stayRight"); //анимация юнита
            arr.append(nul); // Начальные координаты юнита
            arr.append(nul);

            arr.append(1); // 1 полигон для текстуры
            arr.append(4); // 4 точки
            arr.append(nul);    arr.append(nul);
            arr.append(170);    arr.append(nul);
            arr.append(170);    arr.append(128);
            arr.append(nul);    arr.append(128);

            arr.append(2); // 2 полигона для физики
            arr.append(4); // 4 точки
            arr.append(40);     arr.append(10);
            arr.append(120);    arr.append(10);
            arr.append(120);    arr.append(110);
            arr.append(40);     arr.append(110);

            arr.append(4);
            arr.append(40);     arr.append(110);
            arr.append(120);    arr.append(110);
            arr.append(90);     arr.append(128);
            arr.append(70);     arr.append(128);

            // добавление списка полигонов физики
            arr.append("DYNAMIC");
            arr.append(8); // Количество анимаций
            arr.append("dragon_runRight");
                arr.append("runRight");
            arr.append("dragon_runLeft");
                arr.append("runLeft");
            arr.append("dragon_stayLeft");
                arr.append("stayLeft");
            arr.append("dragon_stayRight");
                arr.append("stayRight");
            arr.append("dragon_jumpLeft");
                arr.append("jumpLeft");
            arr.append("dragon_jumpRight");
                arr.append("jumpRight");
            arr.append("dragon_fallLeft");
                arr.append("fallLeft");
            arr.append("dragon_fallRight");
                arr.append("fallRight");

            arr.append("player");// Имя юнита
        ////////////////////////////////////////////////////

        arr.append(8); //8 entity
        ////////////////////////////////////////////////////
            arr.append("road"); //анимация юнита
            arr.append(nul); // Начальные координаты юнита
            arr.append(190);

            arr.append(1); // 1 полигон для текстуры
            arr.append(4); // 4 точки
            arr.append(nul);    arr.append(nul);
            arr.append(44);     arr.append(24);
            arr.append(44);     arr.append(64);
            arr.append(nul);    arr.append(64);

            arr.append(1); // 2 полигона для физики
            arr.append(4); // 4 точки
            arr.append(nul);    arr.append(10);
            arr.append(44);     arr.append(34);
            arr.append(44);     arr.append(40);
            arr.append(4);      arr.append(40);

            // добавление списка полигонов физики
            arr.append("STATIC");
            arr.append(nul); // Количество анимаций

            arr.append("dnishe1");// Имя юнита
        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////
            arr.append("road"); //анимация юнита
            arr.append(64); // Начальные координаты юнита
            arr.append(190);

            arr.append(1); // 1 полигон для текстуры
            arr.append(4); // 4 точки
            arr.append(nul);    arr.append(nul);
            arr.append(44);     arr.append(24);
            arr.append(44);     arr.append(64);
            arr.append(nul);    arr.append(64);

            arr.append(1); // 2 полигона для физики
            arr.append(4); // 4 точки
            arr.append(nul);    arr.append(10);
            arr.append(44);     arr.append(34);
            arr.append(44);     arr.append(40);
            arr.append(4);      arr.append(40);

            // добавление списка полигонов физики
            arr.append("STATIC");
            arr.append(nul); // Количество анимаций

            arr.append("dnishe2");// Имя юнита
        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////
            arr.append("road"); //анимация юнита
            arr.append(nul); // Начальные координаты юнита
            arr.append(128);

            arr.append(1); // 1 полигон для текстуры
            arr.append(4); // 4 точки
            arr.append(nul);    arr.append(nul);
            arr.append(44);     arr.append(24);
            arr.append(44);     arr.append(64);
            arr.append(nul);    arr.append(64);

            arr.append(1); // 2 полигона для физики
            arr.append(4); // 4 точки
            arr.append(nul);    arr.append(10);
            arr.append(44);     arr.append(34);
            arr.append(44);     arr.append(40);
            arr.append(4);      arr.append(40);

            // добавление списка полигонов физики
            arr.append("STATIC");
            arr.append(nul); // Количество анимаций

            arr.append("dnishe3");// Имя юнита
        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////
            arr.append("road"); //анимация юнита
            arr.append(nul); // Начальные координаты юнита
            arr.append(220);

            arr.append(1); // 1 полигон для текстуры
            arr.append(4); // 4 точки
            arr.append(nul);    arr.append(nul);
            arr.append(44);     arr.append(24);
            arr.append(44);     arr.append(64);
            arr.append(nul);    arr.append(64);

            arr.append(1); // 2 полигона для физики
            arr.append(4); // 4 точки
            arr.append(nul);    arr.append(10);
            arr.append(44);     arr.append(34);
            arr.append(44);     arr.append(40);
            arr.append(4);      arr.append(40);

            // добавление списка полигонов физики
            arr.append("STATIC");
            arr.append(nul); // Количество анимаций

            arr.append("dnishe4");// Имя юнита
        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////
            arr.append("road"); //анимация юнита
            arr.append(nul); // Начальные координаты юнита
            arr.append(300);

            arr.append(1); // 1 полигон для текстуры
            arr.append(4); // 4 точки
            arr.append(nul);    arr.append(nul);
            arr.append(44);     arr.append(24);
            arr.append(44);     arr.append(64);
            arr.append(nul);    arr.append(64);

            arr.append(1); // 2 полигона для физики
            arr.append(4); // 4 точки
            arr.append(nul);    arr.append(10);
            arr.append(44);     arr.append(34);
            arr.append(44);     arr.append(40);
            arr.append(4);      arr.append(40);

            // добавление списка полигонов физики
            arr.append("STATIC");
            arr.append(nul); // Количество анимаций

            arr.append("dnishe5");// Имя юнита
        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////
            arr.append("road"); //анимация юнита
            arr.append(nul); // Начальные координаты юнита
            arr.append(380);

            arr.append(1); // 1 полигон для текстуры
            arr.append(4); // 4 точки
            arr.append(nul);    arr.append(nul);
            arr.append(44);     arr.append(24);
            arr.append(44);     arr.append(64);
            arr.append(nul);    arr.append(64);

            arr.append(1); // 2 полигона для физики
            arr.append(4); // 4 точки
            arr.append(nul);    arr.append(10);
            arr.append(44);     arr.append(34);
            arr.append(44);     arr.append(40);
            arr.append(4);      arr.append(40);

            // добавление списка полигонов физики
            arr.append("STATIC");
            arr.append(nul); // Количество анимаций

            arr.append("dnishe6");// Имя юнита
        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////
            arr.append("road"); //анимация юнита
            arr.append(nul); // Начальные координаты юнита
            arr.append(450);

            arr.append(1); // 1 полигон для текстуры
            arr.append(4); // 4 точки
            arr.append(nul);    arr.append(nul);
            arr.append(44);     arr.append(24);
            arr.append(44);     arr.append(64);
            arr.append(nul);    arr.append(64);

            arr.append(1); // 2 полигона для физики
            arr.append(4); // 4 точки
            arr.append(nul);    arr.append(10);
            arr.append(44);     arr.append(34);
            arr.append(44);     arr.append(40);
            arr.append(4);      arr.append(40);

            // добавление списка полигонов физики
            arr.append("STATIC");
            arr.append(nul); // Количество анимаций

            arr.append("dnishe7");// Имя юнита
        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////
            arr.append("road"); //анимация юнита
            arr.append(nul); // Начальные координаты юнита
            arr.append(580);

            arr.append(1); // 1 полигон для текстуры
            arr.append(4); // 4 точки
            arr.append(nul);    arr.append(nul);
            arr.append(44);     arr.append(24);
            arr.append(44);     arr.append(64);
            arr.append(nul);    arr.append(64);

            arr.append(1); // 2 полигона для физики
            arr.append(4); // 4 точки
            arr.append(nul);    arr.append(10);
            arr.append(44);     arr.append(34);
            arr.append(44);     arr.append(40);
            arr.append(4);      arr.append(40);

            // добавление списка полигонов физики
            arr.append("STATIC");
            arr.append(nul); // Количество анимаций

            arr.append("dnishe8");// Имя юнита
        ////////////////////////////////////////////////////

        this->saveRes(arr);
}
