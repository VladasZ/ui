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
    enable_touch();
    on_touch = [&](Touch* touch) {
        if (!touch->is_began()) {
            return;;
        }
        _is_selected = !_is_selected;
        on_value_changed(_is_selected);
    };
}

bool Switch::is_selected() const {
    return _is_selected;
}

void Switch::_layout() {

    _calculate_absolute_frame();


    static constexpr float indent = 4.0f;

    auto half_widht = _frame.size.width / 2;

    _switch->edit_frame() = {indent,
                             indent,
                              half_widht - indent,
                              _frame.size.height - indent * 2
    };

    if (_is_selected) {
        _switch->edit_frame().origin.x += half_widht - indent;
    }

    background_color = _is_selected ? Color::green : Color::clear;

    _layout_subviews();
}
