#pragma once

#include <raylib.h>
#include <vector>
#include "Widgets.hpp"

//Parent class for all layout
class Layout : public Widget
{
    protected:
        std::vector<Widget*> widget_container;
        unsigned int spacing;
    public:
        Layout(Vector2 pos = Vector2{0,0}, unsigned int width = 0, unsigned int height = 0) : Widget(pos, width, height)
        {}
        ~Layout() 
        {
            widget_container.clear();
        }

        virtual void AppendWidget(Widget * widget)
        {
            widget_container.push_back(widget);
            UpdateLayout();
        }
        
        void OnKeyPress(int key) override
        {
            for(Widget* widget : widget_container)
            {
                widget->OnKeyPress(key);
            }
        }

        void OnClick(Vector2 mouse_pos) override
        {
            for(Widget* widget : widget_container)
            {
                widget->OnClick(mouse_pos);
            }
        }

        void OnHoldClick(Vector2 mouse_pos) override
        {
            for(Widget* widget : widget_container)
            {
                widget->OnHoldClick(mouse_pos);
            }
        }

        void OnHover(bool state) override
        {
            for(Widget* widget : widget_container)
            {
                widget->OnHover(state);
            }
        }

        void PopWidget()
        {
            widget_container.pop_back();
        }

        void Update() override
        {
            for(Widget* widget : widget_container)
            {
                widget->Update();
            }
        }

        void Draw() override
        {
            for(Widget* widget : widget_container)
            {
                widget->Draw();
            }
        }
};

class VerticalLayout : public Layout
{
private:
    /* data */
public:
    VerticalLayout(/* args */) : Layout ()
    {
        spacing = 10;
    }
    ~VerticalLayout() {}

    void AppendWidget(Widget * widget) override
    {
        if(widget->GetWidth() > w_width)
        {
            w_width = widget->GetWidth();
        }
        widget_container.push_back(widget);
        w_height += widget->GetHeight();
        UpdateLayout();
    }

    void UpdateLayout() override
    {
        float y = pos.y;
        for(Widget * widget : widget_container)
        {
            widget->ChanePos(Vector2{pos.x, y});
            widget->UpdateLayout();
            y += widget->GetHeight() + spacing;
        }
    }
};


class HorizontalLayout : public Layout
{
    private:
        /*data*/
    public:
        HorizontalLayout() : Layout()
        {
            spacing = 10;
        }

        ~HorizontalLayout()
        {}

        void AppendWidget(Widget * widget) override
        {
            if (widget->GetHeight() > w_height)
            {
                w_height = widget->GetHeight();
            }
            widget_container.push_back(widget);
            w_width += widget->GetWidth();
            UpdateLayout();
        }

        void UpdateLayout() override
        {
            float x = pos.x;
            for(Widget * widget : widget_container)
            {
                widget->ChanePos(Vector2{x, pos.y});
                widget->UpdateLayout();
                x += widget->GetWidth() + spacing;
            }
        }
};

//TODO
class GridLayout : public Layout
{
    protected:
        unsigned int rows, collumns;
    public:
        GridLayout(unsigned int Rows, unsigned int Collumns) : Layout(), rows(Rows), collumns(Collumns)
        {

        }
        ~GridLayout(){}

        void InsertWidget(Widget * widget, unsigned int row, unsigned int coll)
        {
            //TODO
        }
        void AppendWidget(Widget * widget) override
        {
            //TODO
        }
};