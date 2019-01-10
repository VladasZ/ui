//
//  Mouse.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/19/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#ifdef UI_DESKTOP

#include "Mouse.hpp"
#include "Input.hpp"

using namespace ui;

static Touch* mouse_touch = new Touch(1, { }, Touch::Event::Ended);

void Mouse::position_changed(const Point& position) {
   _position = position;
   if (_left_button_state == ButtonState::Up) {
       Input::hover_moved(position);
   } else {
       mouse_touch->location = position;
       mouse_touch->event = Touch::Event::Moved;
       Input::touch_event(mouse_touch);
   }
}

Point Mouse::position() const {
    return _position;
}

void Mouse::set_left_button_state(ButtonState state) {
    _left_button_state = state;
    mouse_touch->event = state == ButtonState::Down ? Touch::Event::Began : Touch::Event::Ended;
    mouse_touch->location = _position;
    Input::touch_event(mouse_touch);
}

Mouse::ButtonState Mouse::left_button_state() const {
    return  _left_button_state;
}

#endif
