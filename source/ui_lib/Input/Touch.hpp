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

#ifdef UI_DESKTOP
#include "Mouse.hpp"
#endif

namespace ui {

class Touch {
public:

    using ID = int64_t;

    enum Event {
        Began,
        Moved,
        Ended
    };

    ID id;
    Point location;
    Event event;

#ifdef UI_DESKTOP
    Mouse::Button button;

    Touch(ID id, const Point& location, Event event, Mouse::Button button);
#else
    Touch(ID id, const Point& location, Event event);
#endif

    bool is_began() const;
    bool is_moved() const;
    bool is_ended() const;

    const char* event_string() const;
    const char* to_string() const;
};

}
