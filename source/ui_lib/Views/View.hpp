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

class Layout;

class View {

    friend Layout;

protected:

    bool _needs_layout = true;
    Rect _frame;
    View* _superview = nullptr;
    std::vector<View*> _subviews;
    std::vector<Layout*> _layouts;

public:

    Color color;

    View(const Rect& = { });
    virtual ~View();

protected:

    virtual void _setup() { }

public:

    void add_subview(View*);
    void add_subview(std::initializer_list<View*>);
    void remove_all_subviews();

public:

    void add_layout(Layout*);
    void add_layout(std::initializer_list<Layout*>);

public:

    Rect frame() const;
    View* superview() const;

public:

    void set_frame(const Rect&);
    void edit_frame(std::function<void(Rect&)>);
    void set_origin(const Point&);
    void set_center(const Point&);

public:

    Point global_point_lo_local(const Point&) const;
    bool contains_global_point(const Point&) const;

protected:

    virtual void _draw();

protected:

    Rect _absolute_frame;
    virtual void _layout();
    void _calculate_absolute_frame();
    void _layout_constraints();
    void _layout_subviews();

protected:

    friend Input;

    std::vector<Touch*> _touches;
    virtual void touch_event(Touch*);

public:

    bool _user_interaction_enabled = false;

    void enable_user_interaction();
    void disable_user_interaction();

public:

    static View* dummy();

};

}
