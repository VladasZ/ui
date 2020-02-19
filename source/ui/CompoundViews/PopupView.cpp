//
//  PopupView.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 19/02/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#include <Input.hpp>
#include "PopupView.hpp"

using namespace ui;
using namespace gm;

void PopupView::set_caption(const std::string& caption) {
    _main_button->set_caption(caption);
}

void ui::PopupView::add_action(const std::string& caption, std::function<void()> action) {
    auto button = new Button();
    button->set_caption(caption);
    button->on_press = action;
    _stack_view->add_subview(button);
    _buttons.push_back(button);
}

void ui::PopupView::_setup() {
    add_subview(_main_button);
    add_subview(_stack_view = new StackView());
    _stack_view->is_hidden = true;

    Input::on_hover_moved = [&](const Point& location) {

        if (!_stack_view->is_hidden) {
            bool visible = _absolute_frame.contains(location) || _stack_view->contains_global_point(location);
            _stack_view->is_hidden = !visible;
            return;
        }

        _stack_view->is_hidden = !_absolute_frame.contains(location);
    };

}

void ui::PopupView::_layout() {
    _calculate_absolute_frame();

    _main_button->edit_frame() = _frame.with_zero_origin();

    auto stack_height = _frame.size.height * _buttons.size();

    _stack_view->edit_frame() =
            { 0,
              -stack_height,
              _frame.size.width,
              stack_height
            };

    _layout_subviews();
}
