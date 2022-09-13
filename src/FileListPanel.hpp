#ifndef FILELISTPANEL_HPP
#define FILELISTPANEL_HPP

#include <wx/wx.h>
#include <wx/panel.h>
#include <vector>
#include <memory>

class FileListPanel : public wxPanel
{
public:

    FileListPanel(wxWindow *parent, int id);

    FileListPanel(wxWindow *parent, std::shared_ptr<std::vector<std::string>> fileNames);
    FileListPanel(wxWindow *parent, int id, std::shared_ptr<std::vector<std::string>> fileNames);

    virtual ~FileListPanel() {};

    enum {
        ID_TITLE = wxID_HIGHEST,
        ID_ENTRY_LOWEST
    };

    void clear();
    void setFilenames(std::shared_ptr<std::vector<std::string>> fileNames);

    void addFile(std::string filename);
private:
    std::vector<wxStaticText *> entries;

    wxBoxSizer *sizer;

    wxStaticText *title;

    int currentIdx = ID_ENTRY_LOWEST;


    
};


#endif
