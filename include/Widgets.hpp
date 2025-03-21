#pragma once
#include <raylib.h>
#include <string>
#include <iostream>
//Parent class for all widgets
class Widget
{
    protected:
        unsigned int w_width = 0, w_height = 0;
        Vector2 pos;
        bool is_focused = false;
    public:
        Widget(Vector2 Pos = Vector2{0,0}, unsigned int width = 0u, unsigned int height = 0u): pos(Pos), w_width(width), w_height(height)
        {}
        ~Widget() {}


        //Recommended to be called within another class and not manually
        virtual void Draw()
        {

        }

        //Recommended to be called within another class and not manually
        virtual void Update()
        {

        }

        virtual void UpdateLayout()
        {

        }

        virtual bool IsHovered(Vector2 mouse_pos)
        {
            return 
            (mouse_pos.x >= pos.x && mouse_pos.x <= pos.x + w_width)
            &&
            (mouse_pos.y >= pos.y && mouse_pos.y <= pos.y + w_height);
        }

        virtual void OnHover(bool state)
        {
            
        }

        void ChanePos(Vector2 new_pos)
        {
            pos = new_pos;
        }

        virtual void OnClick(Vector2 mouse_pos)
        {

        }

        virtual void OnHoldClick(Vector2 mouse_pos)
        {

        }

        virtual void OnKeyPress(int key)
        {}
        
        /*
        virtual void OnKeyHoldDown(int key)
        {}
        */

        Vector2 GetPos() {return pos;}

        unsigned int GetHeight()
        {
            return w_height;
        }

        unsigned int GetWidth()
        {
            return w_width;
        }
        void ShouldFocus(bool state)
        {
            is_focused = state;
        }
};

class Label : public Widget
{
    protected:
        std::string text;
        unsigned int font_size = 16u;
        Color font_color = WHITE;
        Color border_color = BLACK;
        Color background_color = BLACK;

    public:
        Label(std::string Text, Vector2 pos = Vector2{0,0}) : Widget(pos), text(Text)
        {
            //FIXME better calculation for width
            w_width = text.size() * font_size;
            w_height = font_size + 2u;
        }

        void ChangeFontSize(unsigned int new_font_size)
        {
            font_size = new_font_size;
            w_height = font_size + 2u;
        }

        void ChangeFontColor(Color new_font_color)
        {
            font_color = new_font_color;
        }

        void ChangeText(std::string Text)
        {
            text = Text;
        }

        void Draw() override
        {
            DrawRectangle(pos.x, pos.y, w_width, w_height, background_color);
            DrawRectangleLines(pos.x, pos.y, w_width, w_height, border_color);
            DrawText(text.data(), pos.x, pos.y, font_size, font_color);
        }
};

class InputField : public Label
{
    protected:
        Color Focused_Color = BLUE;
        Color Unfocused_Color = PURPLE;

    public:
        InputField(/* args */) : Label("") 
        {
            w_width = 100;
        }
        ~InputField() {}

        void Update() override
        {
            if(!is_focused)
            {
                border_color = Unfocused_Color;
            } else {
                border_color = Focused_Color;
            }

        }

        void OnClick(Vector2 mouse_pos) override
        {
            ShouldFocus(IsHovered(mouse_pos));
        }

        void OnKeyPress(int key_press) override
        {
            if(!is_focused)
            {
                return;
            }
            if(IsKeyDown(KEY_BACKSPACE))
            {
                if(text.size() > 0)
                {
                    text.pop_back();
                }
            } else 
            {
                text += (char)key_press; //TODO Might not work correctly!
            }
        }

        std::string GetText(){return text;}
};

class Button : public Label
{
    //FIXME button gets hovered from way too far (might be a problem on how hover is handled)
    protected:
        Color Hover_Color = BLUE;
        Color Not_Hover_Color = BLACK;
        void (*command)();
    public:
        Button(const char * text) : Label(text)
        {}

        void OnHover(bool state) override
        {
            state? background_color = Hover_Color:
                background_color = Not_Hover_Color;
        }
        
        void SetCommand(void (*func)())
        {
            command = func;
        }

        void OnClick(Vector2 mouse_pos) override
        {
            if(command)
            {
                command();
            }
        }
};

class Slider : public Widget
{
    private:
        unsigned int max_point, min_point;
        float slider_point;
        float value;
        Label * linked_label = nullptr;
        Color Bar_Color = BLACK;
        Color Slider_Color = GRAY;
    public:
        Slider (unsigned int Width = 100u) : Widget(Vector2{0,0}, Width, 100) 
        {
            UpdateLayout();
        }
        ~Slider () {}

        void UpdateLayout() override
        {
            max_point = pos.x + w_width;
            min_point = pos.x;
            slider_point = min_point;
        }

        void OnHoldClick(Vector2 mouse_pos) override
        {
            Vector2 mouse_delta = GetMouseDelta();

            slider_point += mouse_delta.x;
        }

        void OnClick(Vector2 mouse_pos) override
        {
            slider_point = mouse_pos.x;
        }

        void Update() override
        {
            //limit mouse position
            if(slider_point > max_point)
            {
                slider_point = max_point;
            } else if (slider_point < min_point)
            {
                slider_point = min_point;
            }

            //Calculate the value of the slider
            value = (slider_point - min_point) / (max_point - min_point);
            if(linked_label)
            {
                linked_label->ChangeText(std::to_string(value));
            }
        }

        void Draw() override
        {
            //Draw Bar
            DrawRectangle(pos.x, pos.y + pos.y / 2, w_width, w_height / 4, Bar_Color);
            //Draw Slider
            DrawRectangle(slider_point, pos.y, 10, w_height, Slider_Color);
        }

        void LinkToLabel(Label * label)
        {
            linked_label = label;
        }
};