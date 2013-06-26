README
=====

Требования:

Qt 4.8.4
GCC > 4.4

В системе должны быть установлены:
libglew-dev libfreetype6-dev libjpeg-dev libopenal-dev libsndfile-dev libbox2d-dev libxi-dev cmake-gui

1. Установка SFML:
$ cd ~/
$ git clone git@github.com:LaurentGomila/SFML.git
$ cd SFML
$ cmake .
$ sudo make install -j2

2. Установка Box2d
$ cd ~/
$ wget https://box2d.googlecode.com/files/Box2D_v2.2.1.zip
$ unzip Box2D_v2.2.1.zip
$ cd Box2D_v2.2.1/Build
$ cmake-gui ..
На этом этапе нужно убрать сборку static и поставить shared, написать тип сборки Release Остальное по выбору.
$ sudo make install -j2

3. Установка CEGUI
Требуются зависимости: libsilly-dev libfreeimage-dev liblua5.1-dev libtolua++5.1-dev libglm-dev (для винды нужно с сайта cegui скачать dependencies, скомпилить и кинуть в папку с сорцами cegui)
p.s. из практики minizip лучше не выбирать для сборки.
$ cd ~/
$ wget http://downloads.sourceforge.net/project/crayzedsgui/CEGUI%20Mk-2/0.8/cegui-0.8.2.tar.gz
$ tar xzf cegui-0.8.2.tar.gz
$ cd cegui-0.8.2
$ cmake-gui .
Выбрать Render OpenGL и убрать Null, отключить все xml-парсеры кроме Explat 
$ sudo make install -j2

2. Настройка проекта:
$ cd ~/
$ git clone git@github.com:xCryogenx/TDSDL.git
$ mkdir build
$ cp -r TDSDL/resource/* build/

2.1. Запускаем Qt и выбираем ~/TDSDL/source/TDSDL/TDSDL.pro
2.2. Компилим ^_^
