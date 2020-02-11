//
//  Input.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 18/12/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include <list>
#include <stdint.h>

#include "Point.hpp"
#include "Event.hpp"


namespace ui {

class View;
class Touch;

class Input final {

    friend View;

    static inline View* _resizing_view = nullptr;

    static inline std::list<View*> _subscribed_views;
    static inline std::list<View*> _resizable;
    static inline std::list<Touch *> _touches;

    static void _unsubscribe_view(View*);
    static void _unsubscribe_resizable(View*);

public:

    static void process_touch_event(Touch*);

    static inline Event<Touch*> on_touch;

#ifdef DESKTOP_BUILD
    static inline Event<Touch*> on_right_button_drag;
    static void hover_moved(const gm::Point& position);
#endif

};

}
