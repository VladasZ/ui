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

class Window : public View {

public:

    enum class Edge {
        Top         = 0b00000001,
        Bottom      = 0b00000010,
        Left        = 0b00000100,
        Right       = 0b00001000,
        TopLeft     = Top    | Left,
        TopRight    = Top    | Right,
        BottomLeft  = Bottom | Left,
        BottomRight = Bottom | Right,
        None        = 0
    };

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

    EdgeInfo _edge_info;

public:

    Edge get_edge(const Point& point) const;

protected:

    void _layout() override;

};

}
