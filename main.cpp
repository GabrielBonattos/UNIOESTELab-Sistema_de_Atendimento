#include <wx/wx.h>
#include <cstdlib>
#include <map>
#include <ctime>
#include <wx/datetime.h>

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title);

private:
    void OnGerarSenha(wxCommandEvent& event);
    void OnGerarSenhaPreferencial(wxCommandEvent& event);
    void OnChamadoSenha(wxCommandEvent& event);
    void OnChamadoSenhaPreferencial(wxCommandEvent& event);
    void OnEncerrarAtendimento(wxCommandEvent& event);
    void ChamarSenha(int guicheId);
    void ChamarSenhaPreferencial(int guicheId);
    void EncerrarAtendimento(int guicheID);
    void OnTimer(wxTimerEvent&);
    void AtualizarHoraData();


    std::map<int, wxString> guicheSenhas;
    wxListBox* senhaChamadas2;
    wxListBox* senhaList;
    wxListBox* senhaPreferencialList;
    wxListBox* senhaChamados;
    wxStaticText* senha;
    wxString senhaDoGuiche;
    wxString senhaChamada;
    wxStaticText* guiche[4];
    int senhaAtual[4];
    wxStaticText* tempo;
    wxTimer* timer;
    wxDECLARE_EVENT_TABLE();

};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_BUTTON(2, MyFrame::OnGerarSenha)
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

    senha = new wxStaticText(panel, wxID_ANY, "Ultimo chamado: ", wxPoint(600, 20), wxSize(460, 200), wxALIGN_RIGHT);
    senha->SetFont(wxFont(20, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    senhaList = new wxListBox(panel, wxID_ANY, wxPoint(600, 700), wxSize(300, 300));
    senhaPreferencialList = new wxListBox(panel, wxID_ANY, wxPoint(200, 899));
    senhaChamados = new wxListBox(panel, wxID_ANY, wxPoint(650, 100), wxSize(600, 600));

    senhaChamadas2 = new wxListBox(panel, wxID_ANY, wxPoint(300, 700), wxSize(300, 300));
    senhaChamados->SetFont(wxFont(20, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    wxButton* gerarSenha = new wxButton(panel, 2, wxT("Gerar Senha"), wxPoint(20, 220));
    wxButton* gerarSenhaPreferencial = new wxButton(panel, 6, wxT("Gerar Senha Preferencial"), wxPoint(20,270));

    //guiches
    for (int i = 0; i < 4; ++i) {
        guiche[i] = new wxStaticText(panel, wxID_ANY, wxString::Format("Guiche %d", i+1), wxPoint(1400, 50 + i * 150), wxSize(310, 60));
        guiche[i]->SetFont(wxFont(15, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

        new wxButton(panel, 10 + i * 10, wxT("Chamar Senha"), wxPoint(1400, 100 + i * 150));
        new wxButton(panel, 11 + i * 10, wxT("Chamar Senha Preferencial"), wxPoint(1510, 100 + i * 150));
        new wxButton(panel, 12 + i * 10, wxT("Encerrar Atendimento"), wxPoint(1700, 100 + i * 150));
    }

    tempo = new wxStaticText(panel, wxID_ANY, "", wxPoint(700, 800), wxDefaultSize);
    tempo->SetFont(wxFont(20, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    timer = new wxTimer(this);
    Bind(wxEVT_TIMER, &MyFrame::OnTimer, this);
    timer->Start(1000); // Atualizar a cada segundo
    AtualizarHoraData();

    senhaList->Show(false);
    senhaChamadas2->Show(false);
    senhaPreferencialList->Show(false);
    this->ShowFullScreen(true);
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

void MyFrame::OnChamadoSenha(wxCommandEvent &event) {
    int guicheId = (event.GetId() - 10) / 10;
    wxString stringguiche = wxString::Format("%d", guicheId);
    wxLogStatus(stringguiche);
    ChamarSenha(guicheId);
}

void MyFrame::OnChamadoSenhaPreferencial(wxCommandEvent &event) {
    int guicheId = (event.GetId() - 11) / 10;
    ChamarSenhaPreferencial(guicheId);
}

void MyFrame::ChamarSenha(int guicheId) {
    int pegarUltimo = senhaList->GetCount();
    int pegarUltimoPreferencial = senhaPreferencialList->GetCount();
    if(pegarUltimo > 0) {
        if(!guicheSenhas[guicheId].empty()) {
            wxMessageBox("Essa senha ja foi chamada");
            return;
        }
        senhaDoGuiche = senhaList->GetString(pegarUltimo - 1);
        guiche[guicheId]->SetLabel(wxString::Format("Guiche %d: ", guicheId+1) + senhaList->GetString(pegarUltimo - 1));
        senha->SetLabel("Ultimo Chamado: \n" + senhaList->GetString(pegarUltimo - 1) + wxString::Format(" - Guiche %d", guicheId+1));
        senhaDoGuiche = senhaList->GetString(pegarUltimo - 1);
        senhaChamada = senhaDoGuiche + wxString::Format(" Guiche %d", guicheId+1);

        guicheSenhas[guicheId] = senhaDoGuiche;
        senhaChamadas2->InsertItems(1, &senhaDoGuiche, 0);
        senhaList->Delete(pegarUltimo - 1);
        if(senhaDoGuiche.StartsWith("PRI")) {
            senhaPreferencialList->Delete(pegarUltimoPreferencial - 1);
        }

        bool existe = false;
        int quantidadeSenhasChamadas = senhaChamados->GetCount();

        for(int i = 0; i < quantidadeSenhasChamadas; i++) {
            if(senhaChamados->GetString(i) == senhaChamada) {
                existe = true;
                break;
            }
        }
        if(!existe) {
            senhaChamados->InsertItems(1, &senhaChamada, 0);
        }
    }
}

void MyFrame::ChamarSenhaPreferencial(int guicheId) {
    int pegarUltimo = senhaPreferencialList->GetCount();
    if(pegarUltimo > 0) {
        if(!guicheSenhas[guicheId].empty()) {
            wxMessageBox("Essa senha ja foi chamada");
            return;
        }
        guiche[guicheId]->SetLabel(wxString::Format("Guiche %d: ", guicheId+1) + senhaPreferencialList->GetString(pegarUltimo - 1));
        senha->SetLabel("Ultimo chamado: \n" + senhaPreferencialList->GetString(pegarUltimo - 1) + wxString::Format("-Guiche %d", guicheId + 1));
        senhaDoGuiche = senhaPreferencialList->GetString(pegarUltimo -1);
        guicheSenhas[guicheId] = senhaDoGuiche;
        senhaChamadas2->InsertItems(1, &senhaDoGuiche, 0);
        senhaList->Delete(pegarUltimo - 1);
        senhaPreferencialList->Delete(pegarUltimo - 1);
        senhaChamada = senhaDoGuiche + wxString::Format(" Guiche %d", guicheId+1);

        bool existe = false;
        for(int i = 0; i < senhaChamados->GetCount(); i++) {
            if(senhaChamados->GetString(i) == senhaChamada) {
                existe = true;
                break;
            }
        }
        if(!existe) {
            senhaChamados->InsertItems(1, &senhaChamada, 0);
        }
    }
}

void MyFrame::OnEncerrarAtendimento(wxCommandEvent &event) {
    int guicheId = (event.GetId() - 12) / 10;
    EncerrarAtendimento(guicheId);
}

void MyFrame::EncerrarAtendimento(int guicheID) {
    int pegarUltimo = senhaChamadas2->GetCount();
    int pegarUltimoPreferencial = senhaPreferencialList->GetCount();
        if(!guicheSenhas[guicheID].IsEmpty()) {
            wxString senhaAtual = guicheSenhas[guicheID];
            guicheSenhas.erase(guicheID);

            // if(senhaAtual.StartsWith("PRI")) {
            //     senhaPreferencialList->Delete(pegarUltimoPreferencial - 1);
            // }
            for(int i = 0; i < senhaChamadas2->GetCount(); i++) {
                if(senhaChamadas2->GetString(i) == senhaAtual) {
                    senhaChamadas2->Delete(i);
                    break;
                }
            }
            senhaChamada = senhaAtual + wxString::Format(" Guiche %d", guicheID+1);
            for(int i = 0; i < senhaChamados->GetCount(); i++) {
                if(senhaChamados->GetString(i) == senhaChamada) {
                    senhaChamados->Delete(i);
                    break;
                }
            }
        }
        guiche[guicheID]->SetLabel(wxString::Format("Guiche %d: ", guicheID + 1));
}

void MyFrame::AtualizarHoraData() {
    wxDateTime agora = wxDateTime::Now();
    wxString dataHoraStr = agora.Format("%d/%m/%Y %H:%M:%S");
    tempo->SetLabel("Foz Do Iguacu " +dataHoraStr);
}

void MyFrame::OnTimer(wxTimerEvent&) {
    AtualizarHoraData();
}



