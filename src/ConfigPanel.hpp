#ifndef CONFIGPANEL_HPP
#define CONFIGPANEL_HPP

#include <wx/wx.h>

#include <vector>
#include <memory>
#include <string>

class ConfigPanel : public wxPanel
{
public:
    ConfigPanel(wxWindow *parent); 
    ConfigPanel(wxWindow *parent, int id); 

    virtual ~ConfigPanel() {};

    enum {
        ID_Header = wxID_HIGHEST,
        ID_TextBox 
    };

    std::unique_ptr<std::vector<std::string>> getConfigStrings() const;

private:
    wxBoxSizer *sizer;
    
    wxStaticText *header;
    wxTextCtrl *configInput;


};



#endif
