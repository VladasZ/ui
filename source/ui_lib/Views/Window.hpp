//
//  Window.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/19/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include "View.hpp"

namespace ui {

class Input;

class Window : public View {

public:

    Window(const Rect& rect = { });
    ~Window() override;

private:

    struct EdgeInfo {

        inline static const float width = 16;

        float left_min = 0;
        float left_max = 0;

        float right_min = 0;
        float right_max = 0;

        float top_min = 0;
        float top_max = 0;

        float bottom_min = 0;
        float bottom_max = 0;
    };


    friend Input;

    Point _initial_touch;

    void touch_event(Touch* touch) override;

private:

    EdgeInfo _edge_info;
    Rect::Edge _current_edge;

public:

    Rect::Edge get_edge(const Point& point);

protected:

    void _layout() override;

};

}
