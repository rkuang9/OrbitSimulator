#include "include/ui/logger.h"

wxBEGIN_EVENT_TABLE(Logger, wxFrame)
                EVT_SIZE(Logger::ResizeWindow)
wxEND_EVENT_TABLE()

Logger::Logger(UI *parent_ui) : wxFrame(nullptr,
                                        wxID_ANY, "Logger",
                                        wxPoint(parent_ui->frame_point.x, parent_ui->frame_size.GetHeight()),
                                        wxSize(parent_ui->frame_size.GetWidth(), parent_ui->frame_size.GetHeight() / 2))
{
    this->parent_ui = parent_ui;
    std::cout << "logger cons ran\n";

    this->panel = new wxPanel(this, wxID_ANY, parent_ui->frame_point, wxSize(1280, 360));
    this->panel->SetBackgroundColour(wxColour(0, 0, 0));
    this->panel->SetForegroundColour(wxColour(255, 255, 255));
    //this->SetForegroundColour(wxColour(0, 0, 0));

    this->text_ctrl = new wxTextCtrl(this, wxID_ANY, wxString(), wxPoint(0, 0), wxSize(1280, 360),
                                     wxNO_BORDER | wxTE_MULTILINE);
    this->text_ctrl->SetBackgroundColour(wxColour(0, 0, 0));
    this->text_ctrl->SetForegroundColour(wxColour(255, 255, 255));
    this->text_ctrl->SetEditable(false);
    this->text_ctrl->Refresh();
}


Logger::~Logger()
{
    std::cout << "logger destructor\n";
    this->parent_ui = nullptr;
}


void Logger::LogMessage(const std::string &msg)
{
    this->text_ctrl->AppendText(msg);
}

void Logger::LogMessage(const char *msg)
{
    this->text_ctrl->AppendText(wxString(msg));
}


void Logger::LogMessageln(const std::string &msg)
{
    this->text_ctrl->AppendText(msg + "\n");
}


void Logger::LogMessageln(const char *msg)
{
    this->text_ctrl->AppendText(wxString(msg) + "\n");
}


void Logger::ResizeWindow(wxSizeEvent &event)
{
    this->text_ctrl->SetSize(this->GetSize());
}




/*
Logger::Logger(UI *parent_ui) : wxLogWindow(parent_ui, "Log", true, true) {
    this->parent_ui = parent_ui;
    this->Show();
    wxLogNull();


}

Logger::~Logger() {
    std::cout << "logger destructor\n";
    this->parent_ui = nullptr;
}

void Logger::LogMessage(std::string msg)
{
    wxLogMessage(wxString(msg));
}*/
