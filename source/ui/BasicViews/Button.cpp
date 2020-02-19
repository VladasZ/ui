//
//  Button.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 1/28/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#include "Button.hpp"

using namespace ui;
using namespace gm;


Button::Button(const Rect& frame) : View(frame) {
    enable_touch();
    add_subview(_caption_label = new Label());

    on_touch = [&](Touch* touch) {
        if (!is_visible()) return;
        if (touch->is_began()) {
            on_press();
        }
    };
    
}

void Button::set_caption(const std::string& caption) {
    _caption_label->set_text(caption);
    _needs_layout = true;
}
