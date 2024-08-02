#include <wx/wx.h>
#include <cstdlib>
#include <ctime>

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title);

private:
    void OnGerarSenha(wxCommandEvent& event);
    void OnChamadoSenha(wxCommandEvent& event);
    void OnChamadoSenhaPreferencial(wxCommandEvent& event);
    void OnEncerrarAtendimento(wxCommandEvent& event);

    //declarados global
    wxListBox* senhaList;
    wxListBox* senhaPreferencialList;
    wxStaticText* senha;
    wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_BUTTON(10001, MyFrame::OnGerarSenha)
    EVT_BUTTON(2, MyFrame::OnChamadoSenha)
    EVT_BUTTON(3, MyFrame::OnEncerrarAtendimento)
    EVT_BUTTON(4, MyFrame::OnChamadoSenhaPreferencial)
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
    senha = new wxStaticText(panel, wxID_ANY, "Ultimos chamados: ", wxPoint(0, 20), wxSize(310, -1), wxALIGN_RIGHT);
    senhaList = new wxListBox(panel, wxID_ANY, wxPoint(20, 50), wxSize(350, 150));
    senhaPreferencialList = new wxListBox(panel, wxID_ANY, wxPoint(-9999, 9999));
    wxButton* gerarSenha = new wxButton(panel, 10001, wxT("Gerar Senha"), wxPoint(20, 220));
    wxButton* chamarSenha = new wxButton(panel, 2, wxT("Chamar Senha"), wxPoint(120, 220));
    wxButton* encerrarAtendimento = new wxButton(panel, 3, wxT("Encerrar Atendimento"), wxPoint(230, 220));
    wxButton* ChamarSenhaPreferencial = new wxButton(panel, 4, wxT("Chamar senha preferencial"), wxPoint(390,220));

    CreateStatusBar();
    srand((unsigned) time(0));  // Inicializa a semente do gerador de números aleatórios
}

void MyFrame::OnChamadoSenha(wxCommandEvent &event) {
    int pegarUltimo = senhaList->GetCount();
    // wxLogStatus(m_senhaList->GetString(pegarUltimo - 1));

    if(pegarUltimo > 0) {
        senha->SetLabel("Ultimos chamados: " + senhaList->GetString(pegarUltimo - 1));
    }
}

void MyFrame::OnChamadoSenhaPreferencial(wxCommandEvent &event) {
    int pegarUltimo = senhaPreferencialList->GetCount();
    if(pegarUltimo > 0) {
        senha->SetLabel("Ultimos chamados: " + senhaPreferencialList->GetString(pegarUltimo - 1));
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
    int tipo = rand() % 5;
    static int contadorNaoPref = 0;
    static int contadorPref = 0;

    wxString senha;
    if (tipo == 0 || tipo == 1) {
        senha = wxString::Format("NOP%03d", ++contadorNaoPref);
    } else {
        senha = wxString::Format("PRI%03d", ++contadorPref);
        senhaPreferencialList->InsertItems(1, &senha, 0);
    }
    senhaList->InsertItems(1, &senha, 0);
}
