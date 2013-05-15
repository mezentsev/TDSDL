#include "app.h"

#define DEBUG

App::App()
{
    this->screen = new sf::RenderWindow(sf::VideoMode(1000, 800, 32), "SFML Game", sf::Style::Close, sf::ContextSettings(0,0,8));
    this->screen->setFramerateLimit(60); // Ограничение для правильной работы физ.движка
    this->screen->setVerticalSyncEnabled(true);
    //glEnable(GL_TEXTURE_2D);

    this->control = new Control;
    connect(this->control, SIGNAL(end()), this, SLOT(Close()));

    this->_textures   = new Resources<sf::Texture>();
    this->_sprites    = new Resources<sf::Sprite>();
    this->_entities   = new Resources<Entity>();
    this->_anims      = new Resources<Animation>();
    this->_cameras    = new Resources<sf::View>();

    this->world = new b2World(b2Vec2(0.f, 15.0f));
    this->listener = new ContactListener();
    this->world->SetContactListener(listener);

    this->SCALE = 30.f;
    this->resPath = "resource.tdsdl";

    this->levels();
    this->lights = new ltbl::LightSystem(AABB(Vec2f(0.0f, 0.0f), Vec2f(static_cast<float>(this->screen->getSize().x), static_cast<float>(this->screen->getSize().y))), this->screen, "data/lightFin.png", "data/shaders/lightAttenuationShader.frag"
                         );

//    this->ls = new ltbl::LightSystem(
//                         AABB(
//                            Vec2f(0.0f, 0.0f),
//                            Vec2f(100.f,200.f)
//                              ),
//                         this->screen, std::string("data/lightFin.png"), std::string("data/shaders/lightAttenuationShader.frag")
//                         );
}

bool App::Load()
{
    /**********************  Загрузка изображений ************************/
    sf::Texture *image = new sf::Texture();
    if (!image->loadFromFile("images/units/main_hero/hero_runLeft.png")) return false;
    image->setSmooth(true);
    image->setRepeated(true);
    _textures->add(image,"hero_runLeft");

    image = new sf::Texture();
    if (!image->loadFromFile("images/units/main_hero/hero_runRight.png")) return false;
    image->setSmooth(true);
    image->setRepeated(true);
    _textures->add(image,"hero_runRight");

    image = new sf::Texture();
    if (!image->loadFromFile("images/units/main_hero/hero_stayLeft.png")) return false;
    image->setSmooth(true);
    image->setRepeated(true);
    _textures->add(image,"hero_stayLeft");

    image = new sf::Texture();
    if (!image->loadFromFile("images/units/main_hero/hero_stayRight.png")) return false;
    image->setSmooth(true);
    image->setRepeated(true);
    _textures->add(image,"hero_stayRight");

    image = new sf::Texture();
    if (!image->loadFromFile("images/units/main_hero/hero_jumpLeft.png")) return false;
    image->setSmooth(true);
    image->setRepeated(true);
    _textures->add(image,"hero_jumpLeft");

    image = new sf::Texture();
    if (!image->loadFromFile("images/units/main_hero/hero_jumpRight.png")) return false;
    image->setSmooth(true);
    image->setRepeated(true);
    _textures->add(image,"hero_jumpRight");

    image = new sf::Texture();
    if (!image->loadFromFile("images/units/main_hero/hero_fightLeft.png")) return false;
    image->setSmooth(true);
    image->setRepeated(true);
    _textures->add(image,"hero_fightLeft");

    image = new sf::Texture();
    if (!image->loadFromFile("images/units/main_hero/hero_fightRight.png")) return false;
    image->setSmooth(true);
    image->setRepeated(true);
    _textures->add(image,"hero_fightRight");

    image = new sf::Texture();
    if (!image->loadFromFile("images/road.png")) return false;
    image->setSmooth(true);
    image->setRepeated(true);
    _textures->add(image,"road");

    image = new sf::Texture();
    if (!image->loadFromFile("images/background.png")) return false;
    image->setSmooth(true);
    image->setRepeated(true);
    _textures->add(image,"background");
    /*********************************************************************/


    /***************  Установка изображений справйтам  *******************/
    sf::Sprite *spr = new sf::Sprite(*_textures->getRes("hero_runLeft"));
    this->_sprites->add(spr, "hero_runLeft");

    spr = new sf::Sprite(*_textures->getRes("hero_runRight"));
    this->_sprites->add(spr, "hero_runRight");

    spr = new sf::Sprite(*_textures->getRes("hero_stayLeft"));
    this->_sprites->add(spr, "hero_stayLeft");

    spr = new sf::Sprite(*_textures->getRes("hero_stayRight"));
    this->_sprites->add(spr, "hero_stayRight");

    spr = new sf::Sprite(*_textures->getRes("hero_jumpLeft"));
    this->_sprites->add(spr, "hero_jumpLeft");

    spr = new sf::Sprite(*_textures->getRes("hero_jumpRight"));
    this->_sprites->add(spr, "hero_jumpRight");

    spr = new sf::Sprite(*_textures->getRes("hero_fightLeft"));
    this->_sprites->add(spr, "hero_fightLeft");

    spr = new sf::Sprite(*_textures->getRes("hero_fightRight"));
    this->_sprites->add(spr, "hero_fightRight");

    spr = new sf::Sprite(*_textures->getRes("road"));
    this->_sprites->add(spr, "road");

    spr = new sf::Sprite(*_textures->getRes("background"));
    spr->setTextureRect(sf::IntRect(0,0,1000,800)); //TODO: ширина и высота
    this->_sprites->add(spr, "background");
    /*********************************************************************/


    /***************  Создание анимаций из спрайта  **********************/
    Animation * anim = new Animation(this->_sprites->getRes("hero_runLeft"), 6, 9, 0);
    this->_anims->add(anim, "hero_runLeft");

    anim = new Animation(this->_sprites->getRes("hero_runRight"), 6, 9, 0);
    this->_anims->add(anim, "hero_runRight");

    anim = new Animation(this->_sprites->getRes("hero_stayLeft"), 5, 7, 0);
    this->_anims->add(anim, "hero_stayLeft");

    anim = new Animation(this->_sprites->getRes("hero_stayRight"), 5, 7, 0);
    this->_anims->add(anim, "hero_stayRight");

    anim = new Animation(this->_sprites->getRes("hero_jumpLeft"), 1, 1, 0);
    this->_anims->add(anim, "hero_jumpLeft");

    anim = new Animation(this->_sprites->getRes("hero_jumpRight"), 1, 1, 0);
    this->_anims->add(anim, "hero_jumpRight");

    anim = new Animation(this->_sprites->getRes("hero_fightLeft"), 1, 1, 0);
    this->_anims->add(anim, "hero_fightLeft");

    anim = new Animation(this->_sprites->getRes("hero_fightRight"), 1, 1, 0);
    this->_anims->add(anim, "hero_fightRight");

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
    polygon_Player.setPoint(1, sf::Vector2f(150,0));
    polygon_Player.setPoint(2, sf::Vector2f(150,128));
    polygon_Player.setPoint(3, sf::Vector2f(0,128));
    polygon_Player.setOutlineColor(sf::Color::Red);
    polygon_Player.setOutlineThickness(1.f);

    sf::ConvexShape polygon_PlayerPhys(4);
    polygon_PlayerPhys.setPoint(0, sf::Vector2f(40,0));
    polygon_PlayerPhys.setPoint(1, sf::Vector2f(120,0));
    polygon_PlayerPhys.setPoint(2, sf::Vector2f(120,100));
    polygon_PlayerPhys.setPoint(3, sf::Vector2f(40,100));

    sf::ConvexShape polygon_PlayerPhys2(4);
    polygon_PlayerPhys2.setPoint(0, sf::Vector2f(40,105));
    polygon_PlayerPhys2.setPoint(1, sf::Vector2f(120,105));
    polygon_PlayerPhys2.setPoint(2, sf::Vector2f(120,128));
    polygon_PlayerPhys2.setPoint(3, sf::Vector2f(40,128));

    QList<sf::ConvexShape> polygon_PlayerPhysList;
    polygon_PlayerPhysList.append(polygon_PlayerPhys);
    //polygon_PlayerPhysList.append(polygon_PlayerPhys2);

    sf::ConvexShape polygon_Ground(4);
    polygon_Ground.setPoint(0, sf::Vector2f(0,0));
    polygon_Ground.setPoint(1, sf::Vector2f(44,24));
    polygon_Ground.setPoint(2, sf::Vector2f(44,64));
    polygon_Ground.setPoint(3, sf::Vector2f(0,64));
    polygon_Ground.setOutlineColor(sf::Color::Red);
    polygon_Ground.setOutlineThickness(1.f);

    sf::ConvexShape polygon_GroundPhys(4);
    polygon_GroundPhys.setPoint(0, sf::Vector2f(0,0));
    polygon_GroundPhys.setPoint(1, sf::Vector2f(64,0));
    polygon_GroundPhys.setPoint(2, sf::Vector2f(64,64));
    polygon_GroundPhys.setPoint(3, sf::Vector2f(0,64));


    QList<sf::ConvexShape> polygon_GroundPhysList;
    polygon_GroundPhysList.append(polygon_GroundPhys);

    /***************  Создание игрока, назначение стандартной анимации ********************/
    Unit *ent = new Unit(this->_anims->getRes("hero_stayRight"), 200, -150, polygon_Player, polygon_PlayerPhysList, this->world, Physics::DYNAMIC, this->SCALE);
    ent->addAnim(this->_anims->getRes("hero_runRight"), "runRight");
    ent->addAnim(this->_anims->getRes("hero_runLeft"), "runLeft");
    ent->addAnim(this->_anims->getRes("hero_stayLeft"), "stayLeft");
    ent->addAnim(this->_anims->getRes("hero_stayRight"), "stayRight");
    ent->addAnim(this->_anims->getRes("hero_jumpLeft"), "jumpLeft");
    ent->addAnim(this->_anims->getRes("hero_jumpRight"), "jumpRight");
    ent->addAnim(this->_anims->getRes("hero_fightLeft"), "fightLeft");
    ent->addAnim(this->_anims->getRes("hero_fightRight"), "fightRight");
    this->_entities->add(ent,"player");
//    /**************************************************************************************/
    Unit *ent2 = new Unit(this->_anims->getRes("hero_stayLeft"), 250, 0, polygon_Player, polygon_PlayerPhysList, this->world, Physics::DYNAMIC, this->SCALE);
    this->_entities->add(ent2,"enemy");
    Unit *ent3 = new Unit(this->_anims->getRes("hero_stayLeft"), 200, 0, polygon_Player, polygon_PlayerPhysList, this->world, Physics::DYNAMIC, this->SCALE);
    this->_entities->add(ent3,"enemy1");
    /**************************************************************************************/


    /***************  Создание окружения, назначение стандартной анимации ********************/
    Entity *ents = NULL;

    ents = new Entity(this->_anims->getRes("road"), 0,190, polygon_Ground, polygon_GroundPhysList, this->world, Physics::STATIC, this->SCALE);
    this->_entities->add(ents,"dnishe1");

    ents = new Entity(this->_anims->getRes("road"), 64,190, polygon_Ground, polygon_GroundPhysList, this->world, Physics::STATIC, this->SCALE);
    this->_entities->add(ents,"dnishe2");

    ents = new Entity(this->_anims->getRes("road"), 128,190, polygon_Ground, polygon_GroundPhysList, this->world, Physics::STATIC, this->SCALE);
    this->_entities->add(ents,"dnishe3");

    ents = new Entity(this->_anims->getRes("road"), 192,190, polygon_Ground, polygon_GroundPhysList, this->world, Physics::STATIC, this->SCALE);
    this->_entities->add(ents,"dnishe4");

    ents = new Entity(this->_anims->getRes("road"), 256,190, polygon_Ground, polygon_GroundPhysList, this->world, Physics::STATIC, this->SCALE);
    this->_entities->add(ents,"dnishe5");

    ents = new Entity(this->_anims->getRes("road"), 320,190, polygon_Ground, polygon_GroundPhysList, this->world, Physics::STATIC, this->SCALE);
    this->_entities->add(ents,"dnishe6");

    ents = new Entity(this->_anims->getRes("road"), 384,190, polygon_Ground, polygon_GroundPhysList, this->world, Physics::STATIC, this->SCALE);
    this->_entities->add(ents,"dnishe7");

    ents = new Entity(this->_anims->getRes("road"), 448,190, polygon_Ground, polygon_GroundPhysList, this->world, Physics::STATIC, this->SCALE);
    this->_entities->add(ents,"dnishe9");

    ents = new Entity(this->_anims->getRes("road"), 512,150, polygon_Ground, polygon_GroundPhysList, this->world, Physics::STATIC, this->SCALE);
    this->_entities->add(ents,"dnishe10");

    ents = new Entity(this->_anims->getRes("road"), 512,-60, polygon_Ground, polygon_GroundPhysList, this->world, Physics::STATIC, this->SCALE);
    this->_entities->add(ents,"dnishe11");

    ents = new Entity(this->_anims->getRes("road"), -380,50, polygon_Ground, polygon_GroundPhysList, this->world, Physics::STATIC, this->SCALE);
    this->_entities->add(ents,"dnishe12");
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

    // Create a light
    ltbl::Light_Point* testLight = new ltbl::Light_Point();
    testLight->m_intensity = 2.0f;
    testLight->m_center = Vec2f(200.0f, 200.0f);
    testLight->m_radius = 600.0f;
    testLight->m_size = 15.0f;
    testLight->m_spreadAngle = ltbl::pifTimes2;
    testLight->m_softSpreadAngle = 0.0f;
    testLight->CalculateAABB();

    testLight->m_bleed = 0.4f;
    testLight->m_linearizeFactor = 0.2f;

    this->lights->AddLight(testLight);

    testLight->SetAlwaysUpdate(true);

    // Create an emissive light
    ltbl::EmissiveLight* emissiveLight = new ltbl::EmissiveLight();

    sf::Texture text;

    if(!text.loadFromFile("data/emissive.png"))
        abort();

    emissiveLight->SetTexture(&text);

    emissiveLight->SetRotation(45.0f);

    emissiveLight->m_intensity = 1.3f;

    this->lights->AddEmissiveLight(emissiveLight);

    emissiveLight->SetCenter(Vec2f(500.0f, 500.0f));

    // Create a hull by loading it from a file
    ltbl::ConvexHull* testHull = new ltbl::ConvexHull();

    if(!testHull->LoadShape("data/testShape.txt"))
        abort();

    // Pre-calculate certain aspects
    testHull->CalculateNormals();
    testHull->CalculateAABB();

    testHull->SetWorldCenter(Vec2f(300.0f, 300.0f));

    testHull->m_renderLightOverHull = true;

    this->lights->AddConvexHull(testHull);
    this->lights->m_useBloom = true;

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

        // TODO написать функцию setView
        //this->lights->view.setCenter(sf::Vector2f(this->screen->getPosition()));

        sf::Vector2i mousePos = sf::Mouse::getPosition(*this->screen);

        // Update light
        testLight->SetCenter(Vec2f(static_cast<float>(mousePos.x), static_cast<float>(this->screen->getSize().y) - static_cast<float>(mousePos.y)));

        this->screen->setView(*mainCamera);
        this->lights->SetView(*mainCamera);

        this->screen->draw(*(_sprites->getRes("background")));

        this->lights->RenderLights();

                // Draw the lights
        this->lights->RenderLightTexture();

        QMap<QString, Entity*>::iterator i;
        for (i = _entities->getBegin(); i != _entities->getEnd(); ++i)
        {
            this->screen->draw((*i)->animate(this->freq));
            #ifdef DEBUG
            foreach (sf::ConvexShape shape, (*i)->getPhysShapeList()) {
                this->screen->draw(shape);
            }
            #endif
        }

        this->screen->display();

        //this->Render();
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

    this->screen->draw(*(_sprites->getRes("background")));

    QMap<QString, Entity*>::iterator i;
    for (i = _entities->getBegin(); i != _entities->getEnd(); ++i)
    {
        this->screen->draw((*i)->animate(this->freq));
        #ifdef DEBUG
        foreach (sf::ConvexShape shape, (*i)->getPhysShapeList()) {
            this->screen->draw(shape);
        }
        #endif
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
    delete this->lights;
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
