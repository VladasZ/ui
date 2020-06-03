//
//  TextField.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 03/06/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#include "Keyboard.hpp"
#include "TextField.hpp"

using namespace ui;



void TextField::setup() {
    init_view(_cursor, { 2, _font->height() });
    _cursor->background_color = Color::black;

    Keyboard::on_key_pressed = [&] (Key key) {
        Ping;
        set_text(_text + key);
    };

    Keyboard::on_backspace = [&] {
        backspace();
    };

}

void TextField::layout_subviews() {
    Label::layout_subviews();
    _cursor->stick_to(_content_view, Edge::Right);
}
