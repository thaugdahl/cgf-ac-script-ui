#include "MyFrame.hpp"
#include <wx/clipbrd.h>
#include <wx/timer.h>
#include <wx/event.h>


MyFrame::MyFrame()
    : wxFrame(NULL, ID_MyFrame, "GRDECL Converter")
{
    setupMenuBar();    

    files = std::make_shared<std::vector<std::string>>();

    Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MyFrame::OnButtonClick, this, ID_MyBtn);

    myROText = new wxStaticText(this, ID_MyROText, "No active task.", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL);

    myBtn = new wxButton(this, ID_StartBtn, "Start Processing");

    sizer = new wxBoxSizer(wxVERTICAL);

    sizer->Add(myROText, 0, wxEXPAND | wxALL, 5);

    timer = new RenderTimer(this);

    Bind(wxEVT_PAINT, &MyFrame::OnPaint, this, ID_MyFrame);

    fileListPanel = new FileListPanel(this, ID_FileListPanel);

    // configPane = new wxTextCtrl(this, ID_ConfigInput, "Configuration...\nPCW=Pth_x\nPCW=Pth_z", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);

    // configPane->SetMaxSize({99999, 100});
    
    configPanel = new ConfigPanel(this, ID_ConfigPanel);
    sizer->Add(configPanel, 1, wxEXPAND | wxTOP | wxBOTTOM, 5);

    // sizer->Add(configPane, 1, wxEXPAND | wxTOP | wxBOTTOM, 5);
    sizer->Add(fileListPanel, 1, wxTOP | wxBOTTOM, 5);
    sizer->Add(myBtn, 0, wxEXPAND | wxLEFT, 5);

    this->SetSizer(sizer);
    sizer->Layout();
}

MyFrame::~MyFrame()
{
}

void MyFrame::setupMenuBar()
{
    wxMenu *menuFile = new wxMenu;

    menuFile->AppendSeparator();
    menuFile->Append(ID_FileListOpen, "&Open Files...", "Opens a file select dialog tom choose GRDECL files");

    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);

    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");

    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MyFrame::OnFileSelect, this, ID_FileListOpen);

}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void MyFrame::OnFileSelect(wxCommandEvent &event)
{
    wxFileDialog dialog(this, _("Open Files"), "", "", "", wxFD_MULTIPLE);
    dialog.ShowModal();

    wxArrayString filenames{};
    dialog.GetPaths(filenames);

    wxString cwd = wxGetCwd() + "/";

    if ( files )
        files->clear();

    for ( auto &str : filenames )
    {
        if ( str.find(cwd) != std::string::npos ) {
            str.replace(0, cwd.length(), "");
        }

        files->emplace_back(str);
    }

    if ( fileListPanel )
    {
        fileListPanel->clear();
        fileListPanel->setFilenames(files);
    }

    sizer->Layout();

}

void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a graphical utility for changing labels in GRDECL files exported by Petrel so that Permedia can read them",
            "About this program", wxOK | wxICON_INFORMATION);
}


void MyFrame::OnButtonClick(wxCommandEvent& event)
{

    timer->start();
}

void MyFrame::OnPaint(wxPaintEvent &evt)
{
    // Propagate the event
    evt.Skip(true);
}

void MyFrame::setProgress(int progress)
{
    myROText->SetLabel(std::to_string(progress));
}
