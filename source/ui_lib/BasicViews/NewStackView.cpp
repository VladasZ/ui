//
//  NewStackView.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/29/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#include "NewStackView.hpp"

using namespace ui;

void NewStackView::_layout() {
    _layout_constraints();
    _calculate_absolute_frame();
    _layout_subviews();

    float max_x = 0;

    for (auto sub : _subviews) {
        sub->set_frame({
                           max_x,
                           0,
                           sub->frame().size.width,
                           _frame.size.height
                       });
        max_x = sub->frame().max_x();
    }
}
