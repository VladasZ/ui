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

namespace ui {

class View;
class Touch;
class Window;

class Input final {

    friend View;
    friend Window;

    static inline Window* _resizing_window = nullptr;

    static inline std::list<View*> _subscribed_views;
    static inline std::list<Window*> _windows;
    static inline std::list<Touch*> _touches;

public:

    static void touch_event(Touch* touch);

#ifdef UI_DESKTOP
    static void hover_moved(const Point& position);
#endif

};

}
