//
//  ScrollView.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 26/02/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#include "Log.hpp"
#include "ScrollView.hpp"

using namespace ui;


void ScrollView::_setup() {
    init_view(_vertical_slider);
    
    _vertical_slider->on_value_changed = [&](float value) {
        Logvar(value);
        content_offset.y = _conversion.convert(value);
        Logvar(content_offset.y);
    };
}

void ScrollView::_layout() {
    _calculate_absolute_frame();

    _vertical_slider->edit_frame()   = { 10, _frame.size.height };
    _vertical_slider->place_tr();
    _vertical_slider->edit_frame().origin -= content_offset;

    _conversion.converted_maximum = content_size.height - _frame.size.height;

    _layout_subviews();
}
