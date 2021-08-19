#include "include/ui/ui.h"


enum
{
    MENU_Open,
    MENU_Save,
    MENU_SaveAs,
    MENU_OpenLogger,
    MENU_LogTest,
    MENU_About,
    MENU_Quit,
};


wxBEGIN_EVENT_TABLE(UI, wxFrame)
                EVT_BUTTON(10001, UI::OnButtonClicked)
                EVT_MENU(MENU_SaveAs, UI::SaveFile)
                EVT_MENU(MENU_OpenLogger, UI::OpenLogger)
                EVT_MENU(MENU_Quit, UI::TerminateProgram)
                EVT_MENU(MENU_About, UI::AboutDialogue)
                EVT_KEY_DOWN(UI::KeyPressHandler)
                EVT_SIZE(UI::WindowResize)
                EVT_MOVE(UI::WindowReposition)
wxEND_EVENT_TABLE()

UI::UI(wxPoint point, wxSize size) : wxFrame(nullptr, wxID_ANY, "Simulator", point, size)
{
    this->frame_point = point;
    this->frame_size = size;

    this->SetMinSize(wxSize(this->frame_size.GetWidth() / 2, this->frame_size.GetHeight() / 2));
    this->SetMaxSize(wxSize(1280, 720));

    this->SetBackgroundColour(wxColour(255, 255, 255));


    this->CreateStatusBar(1);

    this->CreateMenuBar();

    this->ShortcutAccelerators();

    this->button = new wxButton(this, 10001, "Add", wxPoint(10, 10), wxSize(150, 50));
}


UI::~UI()
{
    // -mwindows linker option in cmake file makes it so
    wxExit();
}


void UI::CreateMenuBar()
{
    this->menu_bar = new wxMenuBar();

    // menu bar - File
    this->file_menu = new wxMenu();
    this->file_menu->Append(wxID_OPEN, _T("&Open (Ctrl+O)"));
    this->file_menu->Append(wxID_SAVE, _T("&Save   (Ctrl+S)"));
    this->file_menu->Append(MENU_SaveAs, _("&Save As (Ctrl+S)"), _("Save File As"));
    this->file_menu->AppendSeparator();
    this->file_menu->Append(MENU_Quit, _T("&Quit"));
    this->menu_bar->Append(this->file_menu, _T("&File"));

    // menu bar - Tools
    this->tools_menu = new wxMenu();
    this->tools_menu->Append(MENU_OpenLogger, _T("&Open Logger (Ctrl+L)"), _("Open Logger_old"));
    this->tools_menu->Append(MENU_LogTest, _T("&Trigger Log"));
    this->menu_bar->Append(this->tools_menu, _T("&Tools"));

    // menu bar - Help
    this->help_menu = new wxMenu();
    this->help_menu->Append(MENU_About, _T("&About"));
    this->menu_bar->Append(this->help_menu, _T("&Help"));
    this->SetMenuBar(menu_bar);
}


void UI::SaveFile(wxCommandEvent &event)
{
    std::cout << "save file\n";
    wxFileDialog *SaveDialog = new wxFileDialog(
            this, _("Save File As _?"), wxEmptyString, wxEmptyString,
            _("Text files (*.txt)|*.txt|C++ Source Files (*.cpp)|*.cpp|C Source files (*.c) | *.c |C header files (*.h) | *.h"),
            wxFD_SAVE | wxFD_OVERWRITE_PROMPT, wxDefaultPosition);

    // Creates a Save Dialog with 4 file types
    if (SaveDialog->ShowModal() == wxID_OK) // If the user clicked "OK"
    {
        CurrentDocPath = SaveDialog->GetPath();
        // set the path of our current document to the file the user chose to save under
        //MainEditBox->SaveFile(CurrentDocPath); // Save the file to the selected path
        // Set the Title to reflect the file open
        //SetTitle(wxString("Edit - ") << SaveDialog->GetFilename());
    }

    // close save dialogue
    SaveDialog->Destroy();
}


void UI::OnButtonClicked(wxCommandEvent &event)
{
    if (this->logger) {
        this->LogMessageln("Button Clicked");
    }
}


void UI::TerminateProgram(wxCommandEvent &event)
{

    this->confirm_quit = new wxMessageDialog(this, wxT("Quit Program?"), wxT("Error"), wxYES_NO);
    auto result = this->confirm_quit->ShowModal();

    if (result == wxID_YES) {
        this->~UI();
    }
}

void UI::AboutDialogue(wxCommandEvent &event)
{
    this->about_dialogue = new wxMessageDialog(this,
                                               wxT("A desktop orbit simulation program implemented using the Barnes-Hut algorithm for rapid n-body calculations"));
    this->about_dialogue->SetOKLabel("Close");
    this->about_dialogue->ShowModal();
}


void UI::KeyPressHandler(wxKeyEvent &event)
{

    if (this->logger == nullptr) {
        std::cout << "logger not open\n";
    }
    else {
        this->LogMessageln("key code: " + std::to_string(event.GetKeyCode()));
        this->LogMessageln("unicode key: " + std::to_string(event.GetUnicodeKey()));
        this->LogMessageln("");
    }
}


void UI::ShortcutAccelerators()
{
    wxAcceleratorEntry entries[2];
    entries[0].Set(wxACCEL_CTRL, (int) 'L', MENU_OpenLogger);
    entries[1].Set(wxACCEL_CTRL, (int) 'S', MENU_SaveAs);

    this->SetAcceleratorTable(wxAcceleratorTable(2, entries));
}


// parent window must be shown in order for logger to open
void UI::OpenLogger(wxCommandEvent &event)
{
    if (!this->IsShown()) {
        return;
    }

    if (!this->logger) {
        this->logger = new Logger(this);
        this->logger->Show();
    }
    else if (this->logger->IsShown()) {
        this->logger->Hide();
    }
    else {
        this->logger->Show();
    }
}


void UI::WindowResize(wxSizeEvent &event)
{
    if (!this->logger) {
        return;
    }

    //wxPoint(parent_ui->frame_point.x, parent_ui->frame_size.GetHeight());

    this->logger->SetSize(wxSize(this->GetSize().GetWidth(), this->GetSize().GetHeight() / 2));
    //this->panel->SetSize(this->GetSize());
}


void UI::WindowReposition(wxMoveEvent &event)
{
    if (!this->logger) {
        return;
    }

    this->logger->SetPosition(wxPoint(this->GetPosition().x, this->GetSize().GetHeight()));
}


void UI::LogMessage(const char *msg)
/** Logging */
{
    this->logger->LogMessage(msg);
}


void UI::LogMessageln(const char *msg)
{
    this->logger->LogMessageln(msg);
}


void UI::LogMessage(const std::string &msg)
{
    this->logger->LogMessageln(msg);
}


void UI::LogMessageln(const std::string &msg)
{
    this->logger->LogMessageln(msg);
}


void UI::LogMessage(const wxString &msg)
{
    this->logger->LogMessage(msg);
}


void UI::LogMessageln(const wxString &msg)
{
    this->logger->LogMessageln(msg);
}
