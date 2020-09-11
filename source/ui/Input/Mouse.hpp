//
//  Mouse.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/19/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include "Platform.hpp"

#ifdef DESKTOP_BUILD

#define MOUSE

#include <map>

#include "Point.hpp"
#include "Event.hpp"

namespace ui {

class Mouse final {

public:

    enum class Button {
        Left,
        Right,
        Middle
    };

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

    static std::map<Button, std::string>      button_to_string;
    static std::map<ButtonState, std::string> button_state_to_string;
    static std::map<CursorMode, std::string>  cursor_mode_to_string;

	static inline gm::Point position;
	static inline Button button = Button::Left;
	static inline ButtonState button_state = ButtonState::Up;

	static inline gm::Point frame_shift;

	static inline cu::Event<gm::Point> on_moved;

    void set_position(const gm::Point&);
    void set_button_state(Button, ButtonState);

    const char* state_string() const;
};

}

#endif
