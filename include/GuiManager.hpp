#pragma once

#include "Widgets.hpp"
#include "Layouts.hpp"
#include <vector>

//This is used for support with 'normal' raylib programs
class GuiManager
{
    protected:
        std::vector<Widget*> widget_counter;
        Vector2 pos;
        VerticalLayout GuiLayout;
    public:
        GuiManager(Vector2 Pos = Vector2{0,0}) : pos(Pos) 
        {
            //Maybe make it so the user can choose the layout
            GuiLayout.ChanePos(Pos);
            GuiLayout.UpdateLayout();
        }
        ~GuiManager() {}

        void AppendWidget(Widget * widget)
        {
            GuiLayout.AppendWidget(widget);
        }

        void EventUpdate()
        {
            //Keyboard
            //FIXME use key down
            int key_pressed = GetKeyPressed();
            if(key_pressed)
            {
                GuiLayout.OnKeyPress(key_pressed);
            }
            
            //Mouse
            Vector2 mouse_pos = GetMousePosition();
            if(GuiLayout.IsHovered(mouse_pos))
            {
                GuiLayout.OnHover(true);
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    GuiLayout.OnClick(mouse_pos);
                } else if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                {
                    GuiLayout.OnHoldClick(mouse_pos);
                }
            } else {
                GuiLayout.OnHover(false);
            }
            
        }

        void Update()
        {
            GuiLayout.Update();
        }

        void Draw()
        {
            GuiLayout.Draw();
        }
};