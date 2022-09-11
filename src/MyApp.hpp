#ifndef MYAPP_H
#define MYAPP_H
#include <wx/wx.h>

class MyApp : public wxApp
{
public:
    MyApp() {}
    virtual ~MyApp() {}
    virtual bool OnInit();
};

#endif
