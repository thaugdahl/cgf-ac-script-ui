#include "FileListPanel.hpp"
#include <iostream>

FileListPanel::FileListPanel(wxWindow *parent, int id) : wxPanel(parent, id, wxDefaultPosition, wxDefaultSize)
{
    sizer = new wxBoxSizer(wxVERTICAL);
    title = new wxStaticText(this, ID_TITLE, "Selected Files");
    title->SetFont(wxFont(18, wxMODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, true) );
    sizer->Add(title, 0, wxEXPAND | wxLEFT, 10);

    this->SetSizer(sizer);
    this->Show(false);
}

FileListPanel::FileListPanel(wxWindow *parent, std::shared_ptr<std::vector<std::string>> fileNames) : FileListPanel(parent, wxID_ANY, fileNames)
{
}

FileListPanel::FileListPanel(wxWindow *parent, int id, std::shared_ptr<std::vector<std::string>> fileNames) : FileListPanel(parent, id)
{

    // clear();
    setFilenames(fileNames);

    sizer->Layout();

    this->Show(true);

}

void FileListPanel::clear()
{
    for ( auto &entry : entries )
    {
        sizer->Detach(entry);
        entry->Destroy();
    }

    entries.clear();
    this->Show(false);
}

void FileListPanel::setFilenames(std::shared_ptr<std::vector<std::string>> fileNames)
{
    for ( const std::string &filename : *fileNames)
    {
        currentIdx++;

        auto newEntry = new wxStaticText(this, currentIdx, wxString(filename), wxDefaultPosition, wxDefaultSize);

        entries.push_back(newEntry);  

        sizer->Add(newEntry, 0, wxEXPAND | wxLEFT, 10);
    }

    sizer->Layout();

    this->Show(true);
}
