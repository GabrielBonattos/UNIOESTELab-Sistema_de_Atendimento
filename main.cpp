#include <wx/wx.h>
#include <cstdlib>
#include <ctime>

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title);

private:
    void OnGerarSenha(wxCommandEvent& event);
    void OnGerarSenhaPreferencial(wxCommandEvent& event);
    void OnChamadoSenha(wxCommandEvent& event);
    void OnChamadoSenhaPreferencial(wxCommandEvent& event);
    void OnEncerrarAtendimento(wxCommandEvent& event);

    //declarados global
    wxListBox* senhaList;
    wxListBox* senhaPreferencialList;
    wxStaticText* senha;
    wxStaticText* guiche[4];
    wxDECLARE_EVENT_TABLE();

    int senhaAtual[4];
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_BUTTON(2, MyFrame::OnGerarSenha)
    EVT_BUTTON(3, MyFrame::OnChamadoSenha)
    EVT_BUTTON(4, MyFrame::OnEncerrarAtendimento)
    EVT_BUTTON(5, MyFrame::OnChamadoSenhaPreferencial)
    EVT_BUTTON(6, MyFrame::OnGerarSenhaPreferencial)
    EVT_BUTTON(10, MyFrame::OnChamadoSenha)
    EVT_BUTTON(11, MyFrame::OnChamadoSenhaPreferencial)
    EVT_BUTTON(12, MyFrame::OnEncerrarAtendimento)
    EVT_BUTTON(20, MyFrame::OnChamadoSenha)
    EVT_BUTTON(21, MyFrame::OnChamadoSenhaPreferencial)
    EVT_BUTTON(22, MyFrame::OnEncerrarAtendimento)
    EVT_BUTTON(30, MyFrame::OnChamadoSenha)
    EVT_BUTTON(31, MyFrame::OnChamadoSenhaPreferencial)
    EVT_BUTTON(32, MyFrame::OnEncerrarAtendimento)
    EVT_BUTTON(40, MyFrame::OnChamadoSenha)
    EVT_BUTTON(41, MyFrame::OnChamadoSenhaPreferencial)
    EVT_BUTTON(42, MyFrame::OnEncerrarAtendimento)

wxEND_EVENT_TABLE()

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    MyFrame* frame = new MyFrame("UNIOESTELab - Sistema de atendimento em laboratorio");
    frame->Show(true);
    return true;
}



MyFrame::MyFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600)) {
    wxPanel* panel = new wxPanel(this, wxID_ANY);
    //wxStaticText* ultimoschamados = new wxStaticText(panel, wxID_ANY, wxT("Últimas Chamadas: "), wxPoint(0, 20),wxSize(400, -1), wxALIGN_CENTRE_HORIZONTAL);
    senha = new wxStaticText(panel, wxID_ANY, "Ultimo chamado: ", wxPoint(600, 20), wxSize(460, 200), wxALIGN_RIGHT);
    senha->SetFont(wxFont(20, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    senhaList = new wxListBox(panel, wxID_ANY, wxPoint(650, 100), wxSize(600, 500));
    senhaPreferencialList = new wxListBox(panel, wxID_ANY, wxPoint(-9999, 9999));
    wxButton* gerarSenha = new wxButton(panel, 2, wxT("Gerar Senha"), wxPoint(20, 220));
    wxButton* chamarSenha = new wxButton(panel, 3, wxT("Chamar Senha"), wxPoint(120, 220));
    wxButton* encerrarAtendimento = new wxButton(panel, 4, wxT("Encerrar Atendimento"), wxPoint(230, 220));
    wxButton* ChamarSenhaPreferencial = new wxButton(panel, 5, wxT("Chamar Senha Preferencial"), wxPoint(390,220));
    wxButton* gerarSenhaPreferencial = new wxButton(panel, 6, wxT("Gerar Senha Preferencial"), wxPoint(20,270));

    //guiches
    for (int i = 0; i < 4; ++i) {
        guiche[i] = new wxStaticText(panel, wxID_ANY, wxString::Format("Guiche %d", i+1), wxPoint(1400, 50 + i * 150), wxSize(310, 60));
        guiche[i]->SetFont(wxFont(15, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

        new wxButton(panel, 10 + i * 10, wxT("Chamar Senha"), wxPoint(1400, 100 + i * 150));
        new wxButton(panel, 11 + i * 10, wxT("Chamar Senha Preferencial"), wxPoint(1510, 100 + i * 150));
        new wxButton(panel, 12 + i * 10, wxT("Encerrar Atendimento"), wxPoint(1700, 100 + i * 150));
    }

    this->ShowFullScreen(true);
    //this->ShowFullScreen(true, wxFULLSCREEN_NOSTATUSBAR || wxFULLSCREEN_NOBORDER || wxFULLSCREEN_NOCAPTION);
    CreateStatusBar();
    srand((unsigned) time(0));  // Inicializa a semente do gerador de números aleatórios
}

void MyFrame::OnChamadoSenha(wxCommandEvent &event) {
    int pegarUltimo = senhaList->GetCount();
    // wxLogStatus(m_senhaList->GetString(pegarUltimo - 1));

    if(pegarUltimo > 0) {
        //guiche->SetLabel("Guiche 01: " + senhaList->GetString(pegarUltimo - 1));
    }
}

void MyFrame::OnChamadoSenhaPreferencial(wxCommandEvent &event) {
    int pegarUltimo = senhaPreferencialList->GetCount();
    if(pegarUltimo > 0) {
        senha->SetLabel("Ultimo chamado: " + senhaPreferencialList->GetString(pegarUltimo - 1));
    }
}


void MyFrame::OnEncerrarAtendimento(wxCommandEvent &event) {
    int pegarUltimo = senhaList->GetCount();
    wxLogStatus("clickado");


    if(pegarUltimo > 0) {
        senhaList->Delete(pegarUltimo - 1);
    }

}

void MyFrame::OnGerarSenha(wxCommandEvent& event) {
    static int contadorNaoPref = 0;
    wxString senha;
    senha = wxString::Format("NOP%03d", ++contadorNaoPref);
    senhaList->InsertItems(1, &senha, 0);
}

void MyFrame::OnGerarSenhaPreferencial(wxCommandEvent& event) {
    static int contadorPref = 0;
    wxString senha;
    senha = wxString::Format("PRI%03d", ++contadorPref);
    senhaPreferencialList->InsertItems(1, &senha, 0);
    senhaList->InsertItems(1, &senha, 0);
}
