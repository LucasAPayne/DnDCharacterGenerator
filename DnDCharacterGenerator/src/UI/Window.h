#include <wx/wx.h>

class Window : public wxFrame
{
public:
    Window(const wxString& title, const wxPoint& pos, const wxSize& size);

    void OnGenerateButtonClicked(wxCommandEvent& evt);

public:
    wxPanel* m_Panel = nullptr;
    wxButton* m_GenerateButton = nullptr;

    wxDECLARE_EVENT_TABLE();
};

enum
{
    ID_START_BUTTON = 1
};
