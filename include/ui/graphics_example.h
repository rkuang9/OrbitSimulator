//
// Created by Macross on 9/13/2021.
//

#ifndef ORBITSIMULATOR_GRAPHICS_EXAMPLE_H
#define ORBITSIMULATOR_GRAPHICS_EXAMPLE_H

#include <iostream>
#include <string>
#include <cassert>
#include <cmath>

#include "wx/wx.h"
#include "wx/glcanvas.h"
#include "wx/notebook.h"


class GraphicsEx : public wxGLCanvas
        {
    wxGLContext*	m_context;

        public:
            GraphicsEx(wxFrame* parent, int* args);
            virtual ~GraphicsEx();

            void resized(wxSizeEvent& evt);

            int getWidth();
            int getHeight();

            void render(wxPaintEvent& evt);
            void prepare3DViewport(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y);
            void prepare2DViewport(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y);

            // events
            void mouseMoved(wxMouseEvent& event);
            void mouseDown(wxMouseEvent& event);
            void mouseWheelMoved(wxMouseEvent& event);
            void mouseReleased(wxMouseEvent& event);
            void rightClick(wxMouseEvent& event);
            void mouseLeftWindow(wxMouseEvent& event);
            void keyPressed(wxKeyEvent& event);
            void keyReleased(wxKeyEvent& event);

            DECLARE_EVENT_TABLE()
        };


#endif //ORBITSIMULATOR_GRAPHICS_EXAMPLE_H
