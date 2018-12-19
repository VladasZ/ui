//
//  View.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/5/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include <stdint.h>
#include <vector>

#include "Rect.hpp"
#include "Color.hpp"
#include "Input.hpp"
#include "Touch.hpp"

namespace ui {

class View {

protected:

    bool _needs_layout = true;
    Rect _frame;
    View* _superview = nullptr;
    std::vector<View*> _subviews;

public:

    Color color;

    View(const Rect& rect = { });
    virtual ~View();

    void add_subview(View* view);

public:

    void set_frame(const Rect& frame);
    void set_origin(const Point& origin);
    void set_center(const Point& center);

public:

    virtual void draw();

protected:

    Rect _absolute_frame;
    virtual void _layout();

protected:

    friend Input;

    std::vector<Touch*> _touches;
    void touch_event(Touch* touch);

};

}
