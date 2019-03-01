//
//  Mouse.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/19/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#if DESKTOP_BUILD

#include <iostream>

#include "Mouse.hpp"
#include "Input.hpp"

using namespace ui;

std::map<Mouse::Button, std::string> Mouse::button_to_string = {
    { Mouse::Button::Left,   "Left"   },
    { Mouse::Button::Right,  "Right"  },
    { Mouse::Button::Middle, "Middle" }
};

std::map<Mouse::ButtonState, std::string> Mouse::button_state_to_string = {
    { Mouse::ButtonState::Up,   "Up"   },
    { Mouse::ButtonState::Down, "Down" }
};

std::map<Mouse::CursorMode,  std::string> Mouse::cursor_mode_to_string = {
    { Mouse::CursorMode::Arrow,   "Arrow"   },
    { Mouse::CursorMode::Text,    "Text"    },
    { Mouse::CursorMode::Drag,    "Drag"    },
    { Mouse::CursorMode::HResize, "HResize" },
    { Mouse::CursorMode::VResize, "VResize" }
};

static Touch* mouse_touch = new Touch(1, { }, Touch::Event::Ended, Mouse::Button::Left);

void Mouse::set_position(const Point& position) {
   _position = position;
   if (_button_state == ButtonState::Up) {
       Input::hover_moved(position);
   } else {
       mouse_touch->location = position;
       mouse_touch->event = Touch::Event::Moved;
       Input::touch_event(mouse_touch);
   }
}

void Mouse::set_button_state(Button button, ButtonState state) {
    _button_state = state;
    mouse_touch->event = state == ButtonState::Down ? Touch::Event::Began : Touch::Event::Ended;
    mouse_touch->location = _position;
    mouse_touch->button = button;
    Input::touch_event(mouse_touch);
}

const char* Mouse::state_string() const {
    static std::string result;
    result = std::string() +
            "Button: "    + Mouse::button_to_string      [_button      ] +
            " State: "    + Mouse::button_state_to_string[_button_state] +
            " Position: " + _position.to_string();
    return result.c_str();
}

#endif




