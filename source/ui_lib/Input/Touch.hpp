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
    ui::Point location;
    Event event;

    Touch(ID id, const ui::Point& location, Event event);

    bool is_began() const;
    bool is_moved() const;
    bool is_ended() const;

    const char* event_string() const;
    const char* to_string() const;
};

}
