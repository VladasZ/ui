//
//  Input.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/18/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include "stdint.h"

#include <list>

#include "Point.hpp"
#include "Touch.hpp"
#include "Event.hpp"

namespace ui {

class View;
class Touch;
class Window;

class Input final {

    friend View  ;
    friend Window;

    static inline Window* _resizing_window = nullptr;

    static inline std::list<View  *> _subscribed_views;
    static inline std::list<Window*>          _windows;
    static inline std::list<Touch *>          _touches;

    static void _unsubscribe_view    (View*);
    static void _unsubscribe_window(Window*);

public:

    static void process_touch_event(Touch*);

    static inline Event<Touch*> on_touch;

#if DESKTOP_BUILD
    static inline Event<Touch*> on_right_button_drag;
    static void hover_moved(const gm::Point& position);
#endif

};

}
