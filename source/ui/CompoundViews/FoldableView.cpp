//
//  FoldableView.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 27/02/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#include "FoldableView.hpp"

using namespace ui;


void FoldableView::set_folded(bool folded) {
    _needs_layout = true;
    _folded = folded;
    hidden_view->is_hidden = folded;
    if (folded) {
        _frame.size = { main_view->frame().max_x(), main_view->frame().max_y() };
        return;
    }
    _frame.size.height = hidden_view->frame().max_y();
    _frame.size.width = hidden_view->frame().max_x();
}

void FoldableView::_setup() {
    init_view(_unfold_button);
    _unfold_button->on_press = [&] {
        set_folded(!_folded);
    };
}

void FoldableView::_layout() {
    _calculate_absolute_frame();
    hidden_view->edit_frame().origin.y = main_view->frame().max_y();
    set_folded(_folded);
    _unfold_button->edit_frame() = _frame.with_zero_origin();
    _unfold_button->edit_frame().size.height = main_view->frame().size.height;
    _layout_subviews();
}
