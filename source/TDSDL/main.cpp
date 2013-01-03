#ifdef _WIN32
#include <cstdio>
#elif linux
#include <stdio.h>
#endif

#include "app.h"

#include "SDL/SDL.h"
#include <cstdlib>
#include <ctime>

#undef main

int main ()
{
    App App;
    return App.Execute();
}
