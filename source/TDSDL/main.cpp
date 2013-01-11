//#ifdef _WIN32
//#include <cstdio>
//#elif linux
//#include <stdio.h>
//#endif

#include "app.h"

//#include <cstdlib>
//#include <ctime>

//#undef main

int main ()
{
    App App;
    return App.Execute();
}

//int main()
//{
//    // Create the main window
//    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

//    while (window.IsOpened())
//    {
//        // Clear screen
//        window.Clear();

//        // Update the window
//        window.Display();
//    }

//    return EXIT_SUCCESS;
//}
