//
//  Keyboard.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 2/5/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#include "Keyboard.hpp"

using namespace ui;

static const char backspace = 3;


void Keyboard::add_key_event(Key key, Mod mod, Event event) {
    on_key_event(key, event);

    if (event == Up) return;

    if (key == backspace) {
        on_backspace();
        return;
    }

    Logvar((int)key);
    on_key_pressed(key);
}
