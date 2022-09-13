#ifndef MYFRAME_HPP
#define MYFRAME_HPP

#include <wx/wx.h>
#include "Task.hpp"

#include "ConfigPanel.hpp"
#include "FileListPanel.hpp"
#include <vector>
#include <memory>
#include <string>

enum
{
    ID_MyFrame = 1,
    ID_Hello = 2,
    ID_MyBtn = 3,
    ID_MyTxt,
    ID_MyROText,
    ID_MyGauge,
    ID_FileListPanel,
    ID_FileListOpen,
    ID_ConfigInput,
    ID_ConfigPanel,
    ID_StartBtn
};

class RenderTimer : public wxTimer
{
    wxFrame *pane;
public:
    RenderTimer(wxFrame *pane)
    {
        this->pane = pane;
    }
    void Notify() {
        pane->Refresh();
    }

    void start() {
        wxTimer::Start(10);
    }

};


class MyFrame : public wxFrame
{
public:
    MyFrame();
    virtual ~MyFrame();

    void setProgress(int progress);
private:
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnButtonClick(wxCommandEvent& event);
    void OnPaint(wxPaintEvent& event);
    void OnFileSelect(wxCommandEvent &event);

    void setupMenuBar();

    wxStaticText *myROText;
    wxButton *myBtn;
    wxTextCtrl *myTxt;
    FileListPanel *fileListPanel;

    std::shared_ptr<std::vector<std::string>> files;

    wxBoxSizer *sizer;

    wxTextCtrl *configPane;

    ConfigPanel *configPanel;


    FileProcessorTask *task = nullptr;

    RenderTimer *timer;

    
};


#endif
