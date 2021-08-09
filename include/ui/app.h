#pragma once
#include "wx/wx.h"
#include "ui.h"


class App : public wxApp
{
private:
	UI* frame = nullptr;

public:
	App();
	~App();
	virtual bool OnInit();
};






