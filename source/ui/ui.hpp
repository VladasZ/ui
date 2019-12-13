//
//  ui.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/5/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include "Font.hpp"
#include "Mouse.hpp"
#include "System.hpp"
#include "UIDrawer.hpp"

#define DRAW_DEBUG_FRAMES

namespace ui {

struct config {
    static UIDrawer* drawer();
    static void set_drawer(UIDrawer* drawer);
    static inline Font* default_font = nullptr;
};

#if DESKTOP_BUILD
struct input {
    static Mouse* const mouse;
};
#endif

}

