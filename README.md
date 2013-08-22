README
=====

Требования:


Qt 5.1<br>
GCC 4.8

Сборка для Ubuntu 13.04:

В системе должны быть установлены:<br>
libfreetype6-dev libjpeg-dev libopenal-dev libsndfile-dev libxi-dev cmake-gui

1. Установка SFML:<br>
$ cd ~/<br>
$ git clone git@github.com:LaurentGomila/SFML.git<br>
$ cd SFML<br>
$ cmake .<br>
$ sudo make install -j2<br>
<br>
2. Установка Box2d<br>
$ cd ~/<br>
$ wget https://box2d.googlecode.com/files/Box2D_v2.2.1.zip<br>
$ unzip Box2D_v2.2.1.zip<br>
$ cd Box2D_v2.2.1/Build<br>
$ cmake-gui ..<br>
На этом этапе нужно убрать сборку static и поставить shared, написать тип сборки Release Остальное по выбору.<br>
$ sudo make install -j2<br>
<br>
3. Настройка проекта:<br>
$ cd ~/<br>
$ git clone git@github.com:xCryogenx/TDSDL.git<br>
$ mkdir build<br>
Копируем ресурсы из resources в build 
<br>
3.1. Запускаем Qt и выбираем ~/TDSDL/source/TDSDL/TDSDL.pro<br>
3.2. Компилим ^_^<br>
