//
//  Input.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/18/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include "stdint.h"

#include <vector>

#include "Point.hpp"
#include "Touch.hpp"

namespace ui {

class View;
class Window;

class Input final {

    friend Window;

    static inline std::vector<View*> _subscribed_views;
    static inline std::vector<Window*> _windows;

public:

#ifdef UI_DESKTOP
    static void cursor_moved(const Point& position);
#endif

};

}
