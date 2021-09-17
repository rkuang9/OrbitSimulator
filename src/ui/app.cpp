#include "include/ui/app.h"

#include <iostream>
#include <chrono>
#include "include/simulator_includes.h"

#include "wx/wx.h"
#include "wx/sizer.h"
#include "wx/glcanvas.h"


wxIMPLEMENT_APP(App);

void DevWork()
{
    using namespace space;
    using namespace space::constants;

    list<sObject *> universe;

    universe.add(new sObject(sPoint(1, 1.496e11), 5.9722e24, 10, "Earth"));
    universe.add(new sObject(sPoint(0, 3.84e8), 7.342e22, 10, "Moon"));
    universe.add(new sObject(sPoint(0, 2.279e8), 6.4171e23, 10, "Mars"));
    universe.add(new sObject(sPoint(0, 1), 1.989e30, 10, "Sun"));

    BarnesHut *simulator = new BarnesHut(universe, 10 * AU, 0.5, 0.3);
    simulator->UpdateForcesInOrder(*universe[0], simulator->GetQuadTree().GetRoot());

    for (int i = 0; i < universe.size(); i++) {
        std::cout << universe[i]->GetNetForce() << std::endl;
    }
}

App::App()
{
    DevWork();
}


App::~App()
{
}



bool App::OnInit()
{
	/*frame = new UI(wxPoint(30, 30), wxSize(640, 360));
	frame->Show();
	return true;*/

	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	frame = new wxFrame((wxFrame *)NULL, -1,  wxT("Hello GL World"), wxPoint(50,50), wxSize(400,200));

	int args[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};

	glPane = new GraphicsEx((wxFrame*) frame, args);
	sizer->Add(glPane, 1, wxEXPAND);

	frame->SetSizer(sizer);
	frame->SetAutoLayout(true);

	frame->Show();
	return true;
}




/*
    // measure program execution time
    auto start = std::chrono::high_resolution_clock::now();

    DevWork();

    auto stop = std::chrono::high_resolution_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

    std::cout << std::endl << "Execution Time: " << ms.count() / 1e6 << " ms";
 */