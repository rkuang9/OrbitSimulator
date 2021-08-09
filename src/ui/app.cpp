#include "include/ui/app.h"
#include "include/list.h"
#include "include/barnes-hut/object.h"
#include "include/barnes-hut/quadtree.h"

wxIMPLEMENT_APP(App);



// copy elision, copy constructor not ran, use optimization when compiling
space::object CreateObject(int x, int y, int mass, int velocity, std::string name) {
    return space::object(x, y, mass, velocity, std::move(name));
}

// test code here, main() measures run time
void DevWork()
{
    //std::vector<space::Object> objects;
    //CreateObjects(objects);
    const double AU = 1.496e11;

    space::list<space::object> universe;


    universe.add(CreateObject(10, 10, 10, 10, "a"));
    universe.add(CreateObject(20, 20, 20, 10, "b"));
    universe.add(CreateObject(-30, 30, 30, 10, "c"));
    //list.add(CreateObject(10, 10, 10, 10, "d"));
    //list.add(CreateObject(10, 10, 10, 10, "e"));
    //list.add(CreateObject(10, 10, 10, 10, "f"));

    space::quadtree tree(universe);

    /*
    this->PrintChildren(this->root);
    this->PrintChildren(this->root->top_left);
    this->PrintChildren(this->root->top_left->top_right);
    this->PrintChildren(this->root->top_right);*/
    //tree.PrintChildren(tree.root);
    //tree.PrintChildren(tree.root->top_right);
    //tree.PrintChildren(tree.root->top_left->top_right);

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
	frame = new UI(wxPoint(30, 30), wxSize(640, 360));
	frame->Show();
	wxCommandEvent test = NULL;
	frame->OpenLogger(test);
	return true;
}


