README
=====

Требования: <br>

Qt 4.8.4<br>
GCC > 4.4<br>

В системе должны быть установлены:
libglew-dev libfreetype6-dev libjpeg-dev libopenal-dev libsndfile-dev libbox2d-dev libxi-dev cmake-gui

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
3. Установка CEGUI<br>
Требуются зависимости: libsilly-dev libfreeimage-dev liblua5.1-dev libtolua++5.1-dev libglm-dev (для винды нужно с сайта cegui скачать dependencies, скомпилить и кинуть в папку с сорцами cegui)
p.s. из практики minizip лучше не выбирать для сборки.<br>
$ cd ~/<br>
$ wget http://downloads.sourceforge.net/project/crayzedsgui/CEGUI%20Mk-2/0.8/cegui-0.8.2.tar.gz<br>
$ tar xzf cegui-0.8.2.tar.gz<br>
$ cd cegui-0.8.2<br>
$ cmake-gui .<br>
Выбрать Render OpenGL и убрать Null, отключить все xml-парсеры кроме Explat <br>
$ sudo make install -j2<br>
<br>
2. Настройка проекта:<br>
$ cd ~/<br>
$ git clone git@github.com:xCryogenx/TDSDL.git<br>
$ mkdir build<br>
$ cp -r TDSDL/resource/* build/<br>
<br>
2.1. Запускаем Qt и выбираем ~/TDSDL/source/TDSDL/TDSDL.pro<br>
2.2. Компилим ^_^<br>
