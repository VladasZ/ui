//
//  Button.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 1/28/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#include "Button.hpp"

using namespace ui;

Button::~Button() {
    disable_user_interaction();
}

Button::Button(const Rect& frame) : View(frame) {
    enable_user_interaction();
}

void Button::touch_event(Touch* touch) {
    View::touch_event(touch);
    if (on_touch && touch->is_began())
        on_touch();
}
