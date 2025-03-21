#pragma once

#include <raylib.h>
#include "Widgets.hpp"
#include "Layouts.hpp"
#include "GuiManager.hpp"

class Application
{
    protected:
        unsigned int W_width, W_height;
        GuiManager gui_manager;
        bool is_running = true;
        Color BackGroundColor = WHITE;

    public:
        Application(unsigned int window_width = 1200u, unsigned int window_height = 800u)
        : W_width(window_width), W_height(window_height)
        {}

        ~Application() {}

        void ChangeBackGround(Color new_color)
        {
            BackGroundColor = new_color;
        }
        void InitApp(const char * App_title)
        {
            InitWindow(W_width, W_height, App_title);
        }

        void AppendWidget(Widget * widget)
        {
            gui_manager.AppendWidget(widget);
        }
        
        void AppLoop()
        {
            while (!WindowShouldClose())
            {
                gui_manager.EventUpdate();
                gui_manager.Update();
                BeginDrawing();
                    ClearBackground(BackGroundColor);
                    gui_manager.Draw();
                EndDrawing();
            }
        }
};