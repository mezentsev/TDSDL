#include "guimanager.h"

GUImanager::GUImanager()
{    
    this->isShown = false;
    CEGUI::OpenGLRenderer& renderer = CEGUI::OpenGLRenderer::create();
    CEGUI::System::create( renderer );
    this->rp = static_cast<CEGUI::DefaultResourceProvider*>
            (CEGUI::System::getSingleton().getResourceProvider());

    CEGUI::SchemeManager::getSingleton().createFromFile( "TaharezLook.scheme" );

    CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
    this->root = wmgr.createWindow( "DefaultWindow", "root" );
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow( this->root );
}

GUImanager::~GUImanager()
{
}

void GUImanager::buildWindow(char* name, float x, float y)
{
    if (!this->isShown)
    {
        this->isShown = true;
        CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
        this->fWnd = static_cast< CEGUI::FrameWindow*>(
            wmgr.createWindow( "TaharezLook/FrameWindow", "testWindow" ));

        root->addChild( this->fWnd );

        fWnd->setPosition( CEGUI::UVector2( CEGUI::UDim( x, 0 ), CEGUI::UDim( y, 0 ) ) );
        fWnd->setSize( CEGUI::USize( CEGUI::UDim( 0.5f, 0 ), CEGUI::UDim( 0.5f, 0 ) ) );
        fWnd->setText((CEGUI::utf8 *)name);
    }
    else
        this->destroyWindow();
}

void GUImanager::destroyWindow()
{
    this->isShown = false;
    this->fWnd->destroy();
}
