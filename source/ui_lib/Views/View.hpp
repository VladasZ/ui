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
#include <functional>

#include "Rect.hpp"
#include "Color.hpp"
#include "Input.hpp"
#include "Touch.hpp"
#include "Layout.hpp"

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

protected:

    virtual void _setup() { }

public:

    void add_subview(View* view);
    void remove_all_subviews();

public:

    Rect frame() const;
    View* superview() const;

public:

    void set_frame(const Rect& frame);
    void edit_frame(std::function<void(Rect&)> edit);
    void set_origin(const Point& origin);
    void set_center(const Point& center);

public:

    Point global_point_lo_local(const Point& point) const;
    bool contains_global_point(const Point& point) const;

protected:

    virtual void _draw();

protected:

    Rect _absolute_frame;
    virtual void _layout();
    void _calculate_absolute_frame();
    void _layout_subviews();

protected:

    friend Input;

    std::vector<Touch*> _touches;
    virtual void touch_event(Touch* touch);

public:

    bool _user_interaction_enabled = false;

    void enable_user_interaction();
    void disable_user_interaction();

};

}
