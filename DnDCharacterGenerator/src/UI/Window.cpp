#include "Window.h"

#include "Character/Character.h"
#include "Utils/FillPDF.h"

wxBEGIN_EVENT_TABLE(Window, wxFrame)
	EVT_BUTTON(ID_START_BUTTON, OnGenerateButtonClicked)
wxEND_EVENT_TABLE()

Window::Window(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(nullptr, wxID_ANY, title, pos, size)
{
	m_Panel = new wxPanel(this, wxID_ANY);
	m_GenerateButton = new wxButton(m_Panel, ID_START_BUTTON, "Generate Character", wxPoint(300, 300), wxSize(200, 35));
}

void Window::OnGenerateButtonClicked(wxCommandEvent& evt)
{
	dnd::Character character;
	fillCharacterSheet_1Page(character);
}
