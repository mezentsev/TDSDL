README
=====

Требования:

Qt 4.8.4
GCC 4.4

Сборка для Ubuntu 13.04:

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

2. Настройка проекта:
$ cd ~/
$ git clone git@github.com:xCryogenx/TDSDL.git
$ mkdir build
$ cp -r TDSDL/resource/* build/

2.1. Запускаем Qt и выбираем ~/TDSDL/source/TDSDL/TDSDL.pro
2.2. Компилим ^_^
