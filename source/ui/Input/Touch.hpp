//
//  Touch.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 8/21/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include <stdint.h>

#include "Point.hpp"
#include "Platform.hpp"

#if DESKTOP_BUILD
#include "Mouse.hpp"
#endif

namespace ui {

class Touch {
public:

    using ID = uint64_t;

	static inline constexpr ID no_id = static_cast<ID>(-1);

    enum Event {
        Began,
        Moved,
        Ended
    };

    ID id;
    gm::Point location;
    Event event;

#if DESKTOP_BUILD
    Mouse::Button button;

    Touch(ID id, const gm::Point& location, Event event, Mouse::Button button);
#else
    Touch(ID id, const gm::Point& location, Event event);
#endif

#if DESKTOP_BUILD
    bool is_left_click() const;
    bool is_middle_click() const;
    bool is_right_click() const;
#endif

    bool is_began() const;
    bool is_moved() const;
    bool is_ended() const;

    std::string event_string() const;
    std::string to_string() const;
};

}
