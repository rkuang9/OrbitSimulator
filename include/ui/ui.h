#pragma once

#include "wx/wx.h"
#include "logger.h"

class Logger; // forward declaration since Logger and UI include each other

class UI : public wxFrame, public wxCommandEvent//, public wxKeyEvent
{
public:
    UI(wxPoint point, wxSize size);

    ~UI();

    wxPoint frame_point;
    wxSize frame_size;

    Logger *logger = nullptr;

    wxPanel *panel = nullptr;
    wxButton *button = nullptr;
    wxTextCtrl *textarea = nullptr;
    wxListBox *listbox = nullptr;

    // menu bar
    wxMenuBar *menu_bar = nullptr;
    wxMenu *file_menu = nullptr;
    wxMenu *tools_menu = nullptr;
    wxMenu *help_menu = nullptr;

    // status bar
    wxStatusBar *status_bar = nullptr;

    // quit dialogue box
    wxMessageDialog *confirm_quit = nullptr;

    // about dialogue box
    wxMessageDialog *about_dialogue = nullptr;

public:
    //wxTextCtrl *MainEditBox;
    // The Path to the file we have open
    wxString CurrentDocPath;

    void CreateMenuBar();

    void SaveFile(wxCommandEvent &event);

    void OnButtonClicked(wxCommandEvent &event);

    // confirm closing main window
    void TerminateProgram(wxCommandEvent &event);

    void AboutDialogue(wxCommandEvent &event);

    // keyboard key press event handling
    void KeyPressHandler(wxKeyEvent &event);

    void ShortcutAccelerators();


    // keep logger window underneath main frame
    void WindowResize(wxSizeEvent &event);

    void WindowReposition(wxMoveEvent &event);


    // open and overloaded logging
    void OpenLogger(wxCommandEvent &event);

    void LogMessage(const char *msg);

    void LogMessageln(const char *msg);

    void LogMessage(const std::string &msg);

    void LogMessageln(const std::string &msg);

    void LogMessage(const wxString &msg);

    void LogMessageln(const wxString &msg);

wxDECLARE_EVENT_TABLE();
};

