#include "App.h"
#include "Utils/Random.h"

// Entry point for the application
wxIMPLEMENT_APP(App);

bool App::OnInit()
{
	Random::Init();
	m_Window = new Window("D&D Character Generator", wxPoint(30, 30), wxSize(800, 600));
	m_Window->Show();
	return true;
}
