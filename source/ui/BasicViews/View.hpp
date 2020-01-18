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
#include "Event.hpp"
#include "Color.hpp"
#include "Input.hpp"
#include "Touch.hpp"

namespace ui {

class View {

public:

    using Array = std::vector<View*>;

public:
    
    Touch::ID _touch_id = 0;

    gm::Rect _frame;
    View* _superview = nullptr;

    View::Array _subviews;
    
    bool _needs_layout = true;

public:

    gm::Color background_color;

    View() = default;
    explicit View(const gm::Rect&);
    virtual ~View();

protected:

    virtual void _setup() { }

public:

    void add_subview(View*);
    void add_subviews(std::initializer_list<View*>);

    void remove_all_subviews();
    void remove_from_superview();

public:

    gm::Rect frame() const;
    View* superview() const;

public:

    void set_frame(const gm::Rect&);
    void edit_frame(std::function<void(gm::Rect&)>);
    void set_origin(const gm::Point&);
    void set_center(const gm::Point&);
    void set_size(const gm::Size&);

public:

    gm::Point global_point_lo_local(const gm::Point&) const;
    bool contains_global_point(const gm::Point&) const;

public:

    virtual void _draw();

protected:

    void _draw_rect();
    void _draw_subviews();

protected:

    gm::Rect _absolute_frame;
    virtual void _layout();
    void _calculate_absolute_frame();
    void _layout_subviews();

protected:

    friend Input;

public:

    Event<Touch*> on_touch;
    
    bool _user_interaction_enabled = false;

    void enable_user_interaction();
    void disable_user_interaction();

public:

    static View* dummy(const gm::Rect& = { 28, 28 });

};

}
