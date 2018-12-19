//
//  Mouse.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/19/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#ifdef UI_DESKTOP

#include "Mouse.hpp"

using namespace ui;


void Mouse::position_changed(const Point& position) {
   _position = position;
}

Point Mouse::position() const {
    return  _position;
}

void Mouse::set_left_button_state(ButtonState state) {
    _left_button_state = state;
}

Mouse::ButtonState Mouse::left_button_state() const {
    return  _left_button_state;
}

#endif
