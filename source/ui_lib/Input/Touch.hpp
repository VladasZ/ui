//
//  Touch.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 8/21/18.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

#include <stdint.h>

#include "Point.hpp"

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
};
