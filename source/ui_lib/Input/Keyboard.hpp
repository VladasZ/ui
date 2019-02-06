//
//  Keyboard.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 2/5/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include "Event.hpp"

namespace ui {

class Keyboard {

public:

    using Key = char;

    enum class Event {
        Up     = 0,
        Down   = 1,
        Repeat = 2
    };

    static inline ui::Event<Key, Event> on_key_event;

    static void add_key_event(Key, Event);

};

}
