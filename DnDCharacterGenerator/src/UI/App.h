#include "Window.h"
#include <wx/wx.h>

class App : public wxApp
{
public:
    virtual bool OnInit();

public:
    Window* m_Window = nullptr;
};
