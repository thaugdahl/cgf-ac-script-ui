#include "MyFrame.hpp"
#include <wx/clipbrd.h>
#include <wx/timer.h>
#include <wx/event.h>


MyFrame::MyFrame()
    : wxFrame(NULL, ID_MyFrame, "Hello World")
{
    setupMenuBar();    

    myBtn = new wxButton(this, ID_MyBtn, "Click me");

     Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MyFrame::OnButtonClick, this, ID_MyBtn);

     myROText = new wxStaticText(this, ID_MyROText, "No active task.", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL);

     myTxt = new wxTextCtrl(this, ID_MyTxt, "Stuff");
     sizer = new wxGridSizer(20,1,1,1);

     sizer->Add(myROText, 1, wxEXPAND | wxALL);
     sizer->Add(myTxt, 1, wxEXPAND | wxALL);
     sizer->Add(myBtn, 1, wxEXPAND | wxALL);

     this->SetSizer(sizer);
     sizer->Layout();

     timer = new RenderTimer(this);

     Bind(wxEVT_PAINT, &MyFrame::OnPaint, this, ID_MyFrame);


}

MyFrame::~MyFrame()
{
    delete myBtn;
    delete myTxt;
}

void MyFrame::setupMenuBar()
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
            "Help string shown in status bar for this menu item");

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

    Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);



}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World Example",
            "About Hello World", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets");
}

void MyFrame::OnButtonClick(wxCommandEvent& event)
{
    wxMessageBox("Starting conversion. The application may be unresponsive while processing the file", "Info", wxOK | wxICON_WARNING);

    myTxt->Show(true);
    sizer->Layout();
    this->Refresh();
    this->Update();
    if ( task ) 
        delete task;

    task = new FileProcessorTask(std::string(myTxt->GetValue()), "output.txt");

    task->run();
    timer->start();
}

void MyFrame::OnPaint(wxPaintEvent &evt)
{
    if ( task ) {
        int progress = task->GetProgress();

        if ( task->HasFailed() ) {
            wxMessageBox(task->GetLastError(), "Error!", wxOK | wxICON_ERROR);
            task->finish();
        }
            

        if ( ! task->isFinished() )
            myROText->SetLabel("Processed " + std::to_string(progress) + " lines");
        else {
            myROText->SetLabel("Finished processing " + std::to_string(progress) + " lines");
            task->finish();
        }

    }
}

void MyFrame::setProgress(int progress)
{
    myROText->SetLabel(std::to_string(progress));
}
