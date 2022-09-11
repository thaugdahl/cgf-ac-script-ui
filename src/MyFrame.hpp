#ifndef MYFRAME_HPP
#define MYFRAME_HPP

#include <wx/wx.h>
#include "Task.hpp"

enum
{
    ID_MyFrame = 1,
    ID_Hello = 2,
    ID_MyBtn = 3,
    ID_MyTxt,
    ID_MyROText,
    ID_MyGauge
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
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnButtonClick(wxCommandEvent& event);
    void OnPaint(wxPaintEvent& event);

    void setupMenuBar();

    wxStaticText *myROText;
    wxButton *myBtn;
    wxTextCtrl *myTxt;

    wxGridSizer *sizer;

    FileProcessorTask *task = nullptr;

    RenderTimer *timer;

    
};


#endif
