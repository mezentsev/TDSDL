#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GLRenderer.h>
#include <QString>

class GUImanager
{
private:
    CEGUI::DefaultResourceProvider* rp;
    CEGUI::Window* root;
    CEGUI::FrameWindow* fWnd;
    bool isShown;
public:
    GUImanager();
    ~GUImanager();
    void buildWindow(char* name, float x, float y);
    void destroyWindow();
};

#endif // GUIMANAGER_H
