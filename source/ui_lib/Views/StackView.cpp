//
//  StackView.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/29/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#include "StackView.hpp"

using namespace ui;


void StackView::set_alignment(Alignment alignment) {
    _alignment = alignment;
    _needs_layout = true;
}

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

    if (_alignment == Alignment::Center) {
        for (size_t i = 0; i < _subviews.size(); i++) {
            _subviews[i]->set_center({ _frame.size.width / 2 + _margin, y_position });
            y_position += delta * 2;
        }
        return;
    }

    if (_alignment == Alignment::Left) {
        for (size_t i = 0; i < _subviews.size(); i++) {
            _subviews[i]->set_origin({ _margin, -_subviews[i]->frame().size.height / 2 + y_position });
            y_position += delta * 2;
        }
    }

    if (_alignment == Alignment::Right) {
        for (size_t i = 0; i < _subviews.size(); i++) {
            auto frame = _subviews[i]->frame();
            _subviews[i]->set_origin({ _frame.size.width - frame.size.width - _margin, -frame.size.height / 2 + y_position });
            y_position += delta * 2;
        }
        return;
    }
}
