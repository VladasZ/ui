//
//  StackView.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/29/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#include "StackView.hpp"

using namespace ui;

void StackView::set_margin(float margin) {
    _margin = margin;
    _needs_layout = true;
}

void StackView::_layout() {
    _calculate_absolute_frame();

    if (_subviews.size() == 0)
        return;

    auto delta = _frame.size.height / (_subviews.size() * 2);

    float y_position = delta;

    for (size_t i = 0; i < _subviews.size(); i++) {
        _subviews[i]->edit_frame().origin = {_margin, -_subviews[i]->frame().size.height / 2 + y_position };
        y_position += delta * 2;
    }
}
