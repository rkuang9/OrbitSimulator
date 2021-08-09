#pragma once

#include "wx/wx.h"
#include "ui.h"

class UI; // forward declaration since Logger and UI need each other


class Logger : public wxFrame
{
private:
    UI *parent_ui = nullptr;

    ~Logger();

    wxPanel *panel = nullptr;

    wxTextCtrl *text_ctrl = nullptr;
public:
    explicit Logger(UI *parent_ui);

    void LogMessageln(const char *msg);

    void LogMessage(const char *msg);

    void LogMessageln(const std::string &msg);

    void LogMessage(const std::string &msg);

    void ResizeWindow(wxSizeEvent &event);

wxDECLARE_EVENT_TABLE();
};