#include "app.h"
#include "Box2D/Box2D.h"

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
//    this->_maps     = new Resources<Map>();
//    this->_texts    = new Resources<sf::Text>();

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

    /***************  Создание сущности, назначение стандартной анимации ******************/
    Unit *ent = new Unit(this->_anims->getRes("dragon_stayRight"),0,0,64,64, this->world, Physics::DYNAMIC, this->SCALE);
    ent->addAnim(this->_anims->getRes("dragon_runRight"), "runRight");
    ent->addAnim(this->_anims->getRes("dragon_runLeft"), "runLeft");
    ent->addAnim(this->_anims->getRes("dragon_stayLeft"), "stayLeft");
    ent->addAnim(this->_anims->getRes("dragon_stayRight"), "stayRight");
    ent->addAnim(this->_anims->getRes("dragon_jumpLeft"), "jumpLeft");
    ent->addAnim(this->_anims->getRes("dragon_jumpRight"), "jumpRight");
    ent->addAnim(this->_anims->getRes("dragon_fallLeft"), "fallLeft");
    ent->addAnim(this->_anims->getRes("dragon_fallRight"), "fallRight");
    this->_entities->add(ent,"player");

    ent = new Unit(this->_anims->getRes("dragon_fallLeft"),-60,200,160,64, this->world, Physics::STATIC, this->SCALE);
    this->_entities->add(ent,"dnishe1");

    ent = new Unit(this->_anims->getRes("dragon_fallLeft"),-380,200,100,64, this->world, Physics::STATIC, this->SCALE);
    this->_entities->add(ent,"dnishe2");

    ent = new Unit(this->_anims->getRes("dragon_fallLeft"),180,200,100,64, this->world, Physics::STATIC, this->SCALE);
    this->_entities->add(ent,"dnishe3");
    /*********************************************************************/

    connect(this->control, SIGNAL(setEntControl(Unit::ORDER)), this->_entities->getRes("player"), SLOT(setControl(Unit::ORDER)));

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
        this->world->Step(1/60.f, 8, 3);

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
        ((Unit*)(*i))->doPhysics(this->SCALE);
//        float x = (*i)->phys.getpHbody()->GetPosition().x * this->SCALE;
//        float y = (*i)->phys.getpHbody()->GetPosition().y * this->SCALE;
//        (*i)->setXY(x, y);
    }
//    int BodyCount = 0;
//    for (b2Body* BodyIterator = this->world->GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
//    {
//        if (BodyIterator->GetUserData() == "ХЬЮДЖ")
//        {
//            float x = BodyIterator->GetPosition().x;
//            float y = BodyIterator->GetPosition().y;
//            ->setXY(x, y);
//            BodyCount++;
//        }

//    }
    //mainCamera->setCenter(_entities->getRes("player")->getX(),_entities->getRes("player")->getY());
}

// Функция занимается отображением всего на экране. Она НЕ обрабатывает манипуляции с данными - этим занимается Loop.
void App::Render()
{
    // Обновляем камеру экрана
    this->screen->setView(*mainCamera);

    // Выведем все ресурсы из Entity
    QMap<QString, Entity*>::iterator i;
    for (i = _entities->getBegin(); i != _entities->getEnd(); ++i)
    {
        this->screen->draw(*(*i)->refresh(this->freq));
        //qDebug() << abi::__cxa_demangle(typeid(*i).name(),0,0,0);
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
    //delete this->_maps;
    delete this->_cameras;
    delete this->world;
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
