//
//  ui.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/5/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

namespace ui {

class Font;
#if DESKTOP_BUILD
class Mouse;
#endif
class UIDrawer;

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

