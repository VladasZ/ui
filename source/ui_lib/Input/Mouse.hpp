//
//  Mouse.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/19/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#ifdef UI_DESKTOP

#include "Point.hpp"

namespace ui {

class Mouse final {

public:

    enum class ButtonState {
        Up,
        Down
    };

    enum class CursorMode {
        Arrow,
        Text,
        Drag,
        HResize,
        VResize
    };

private:

    Point _position;
    ButtonState _left_button_state = ButtonState::Up;

public:

    void position_changed(const Point& position);
    Point position() const;

    void set_left_button_state(ButtonState state);
    ButtonState left_button_state() const;
};

}

#endif
