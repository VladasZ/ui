//
//  Switch.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 17/12/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#include "Switch.hpp"

using namespace ui;
using namespace gm;

void Switch::_setup() {
    _switch = new View();
    _switch->background_color = Color::blue;
    add_subview(_switch);
    enable_user_interaction();
    on_touch.subscribe([&](Touch* touch) {
        if (!touch->is_began()) {
            return;;
        }
        is_selected = !is_selected;
        on_value_changed(is_selected);
    });
}

void Switch::_layout() {

    auto half_widht = _frame.size.width / 2;

    _switch->set_frame({
       is_selected ? half_widht : 0,
       0,
       half_widht,
       _frame.size.height
    });

    View::_layout();
}
