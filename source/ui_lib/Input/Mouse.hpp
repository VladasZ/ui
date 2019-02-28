//
//  Mouse.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/19/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#ifdef UI_DESKTOP

#include <map>

#include "Point.hpp"

namespace ui {

class Mouse final {

public:

    enum class Button {
        Left  ,
        Right ,
        Middle,
    };

    enum class ButtonState {
        Up  ,
        Down,
    };

    enum class CursorMode {
        Arrow  ,
        Text   ,
        Drag   ,
        HResize,
        VResize,
    };

    static std::map<Button     , std::string>       button_to_string;
    static std::map<ButtonState, std::string> button_state_to_string;
    static std::map<CursorMode , std::string>  cursor_mode_to_string;

private:

    Point       _position                      ;
    Button      _button       = Button::Left   ;
    ButtonState _button_state = ButtonState::Up;

public:

    void set_position(const Point&)           ;
    void set_button_state(Button, ButtonState);

    const char* state_string() const;
};

}

#endif
