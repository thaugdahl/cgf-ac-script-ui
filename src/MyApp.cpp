#include "MyApp.hpp"
#include "MyFrame.hpp"

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame();

    frame->Show(true);

    return true;
}
