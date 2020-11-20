//
//  Mouse.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/19/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#include "Target.hpp"

#ifdef DESKTOP_BUILD

#include <iostream>

#include "Input.hpp"
#include "Touch.hpp"
#include "Mouse.hpp"

using namespace ui;
using namespace gm;

static Touch* mouse_touch = new Touch(1, { }, Touch::Event::Ended, Mouse::Button::Left);

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

void Mouse::set_position(const Point& _position) {
	frame_shift = _position - Mouse::position;
	Mouse::position = _position;
	on_moved(_position);
   if (button_state == ButtonState::Up) {
       Input::hover_moved(_position);
   } else {
       mouse_touch->location = _position;
       mouse_touch->event = Touch::Event::Moved;
       Input::process_touch_event(mouse_touch);
   }
}

void Mouse::set_button_state(Button _button, ButtonState state) {
    button_state = state;

    auto event = state == ButtonState::Down ? Touch::Event::Began : Touch::Event::Ended;

    if (event == Touch::Event::Began) {
        static Touch::ID id = 0;
        mouse_touch->id = id++;
    }

    mouse_touch->event = event;
    mouse_touch->location = position;
    mouse_touch->button = _button;

    Input::process_touch_event(mouse_touch);
}

const char* Mouse::state_string() const {
    static std::string result;
    result = std::string() +
            "Button: "    + Mouse::button_to_string      [button      ] +
            " State: "    + Mouse::button_state_to_string[button_state] +
            " Position: " + position.to_string();
    return result.c_str();
}

#endif




