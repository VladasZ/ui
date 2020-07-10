//
//  TextField.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 03/06/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#include "Input.hpp"
#include "Keyboard.hpp"
#include "TextField.hpp"

using namespace ui;


void TextField::setup() {
    init_view(_cursor, { 2, _font->height() });
    _cursor->background_color = Color::black;
    _cursor->is_hidden = true;

    Keyboard::on_input = [&] (char key) {
        if (!_is_focused) return;
        set_text(_text + key);
    };

    Keyboard::on_backspace = [&] {
        if (!_is_focused) return;
        backspace();
    };

    enable_touch();

    Input::on_touch = [&] (Touch* touch) {
        _is_focused = false;
        _cursor->is_hidden = true;
    };

    on_touch = [&] (Touch* touch) {
        _is_focused = true;
        _cursor->is_hidden = false;
    };

}

void TextField::layout_subviews() {
    Label::layout_subviews();
    _cursor->stick_to(_content_view, Edge::Right);
}