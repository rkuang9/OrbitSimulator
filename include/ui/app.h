#pragma once
#include "wx/wx.h"
#include "ui.h"
#include "include/ui/graphics_example.h"


class App : public wxApp
{
private:
	//UI* frame = nullptr;

	// OpenGL example
	wxFrame *frame;
	GraphicsEx * glPane;

public:
	App();
	~App();
	virtual bool OnInit();
};






