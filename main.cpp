#include <wx/wx.h>
#include <cstdlib>
#include <ctime>

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title);

private:
    void OnGenerateSenha(wxCommandEvent& event);

    wxStaticText* m_lastCalled;
    wxButton* m_button;
    wxListBox* m_senhaList;

    wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_BUTTON(10001, MyFrame::OnGenerateSenha)
wxEND_EVENT_TABLE()

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    MyFrame* frame = new MyFrame("Gerador de Senhas");
    frame->Show(true);
    return true;
}



MyFrame::MyFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600)) {
    wxPanel* panel = new wxPanel(this, wxID_ANY);
    m_lastCalled = new wxStaticText(panel, wxID_ANY, wxT("Últimas Chamadas:"), wxPoint(0, 20),wxSize(400, -1), wxALIGN_CENTRE_HORIZONTAL);
    m_senhaList = new wxListBox(panel, wxID_ANY, wxPoint(20, 50), wxSize(350, 150));
    m_button = new wxButton(panel, 10001, wxT("Gerar Senha"), wxPoint(20, 220));
    wxButton* criarGuiche = new wxButton(panel, wxID_ANY, wxT("Gerar Guiche"), wxPoint(250, 220));

    srand((unsigned) time(0));  // Inicializa a semente do gerador de números aleatórios
}


void MyFrame::OnGenerateSenha(wxCommandEvent& event) {
    int tipo = rand() % 2;  // 0 para não-preferencial, 1 para preferencial
    static int contadorNaoPref = 100;
    static int contadorPref = 100;

    wxString senha;
    if (tipo == 0) {
        senha = wxString::Format("N%d", ++contadorNaoPref);
    } else {
        senha = wxString::Format("P%d", ++contadorPref);
    }

    m_senhaList->InsertItems(1, &senha, 0);
}
