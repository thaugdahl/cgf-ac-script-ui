#include "ConfigPanel.hpp"
#include "wx/gdicmn.h"

ConfigPanel::ConfigPanel(wxWindow *parent)
    : ConfigPanel(parent, wxID_ANY)
{}


ConfigPanel::ConfigPanel(wxWindow *parent, int id)
    : wxPanel(parent, id, wxDefaultPosition, {9999, 200})
{

    sizer = new wxBoxSizer(wxVERTICAL);

    header = new wxStaticText(this, ID_Header, "Configuration");
    header->SetFont(wxFont(18,
                wxMODERN,
                wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_BOLD,
                true));

    configInput = new wxTextCtrl(this,
            ID_TextBox,
            "PCW=Pth_x\nPCW=Pth_z",
            wxDefaultPosition,
            wxDefaultSize,
            wxTE_MULTILINE);

    sizer->Add(header, 0, wxEXPAND | wxLEFT, 5);
    sizer->Add(configInput, 1, wxEXPAND | wxLEFT, 5);

    this->SetSizer(sizer);

    sizer->Layout();
}

std::unique_ptr<std::vector<std::string>> ConfigPanel::getConfigStrings() const
{
    int numLines = configInput->GetNumberOfLines();

    std::unique_ptr<std::vector<std::string>> result =
        std::make_unique<std::vector<std::string>>();

    for ( int i = 0; i < numLines; i++ )
    {
        result->push_back(std::string(configInput->GetLineText(i)));        
    }

    return result;
}
