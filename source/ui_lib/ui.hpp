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
#include "UIDrawer.hpp"

namespace ui {

struct config {

    static UIDrawer* drawer();
    static void set_drawer(UIDrawer* drawer);

    static inline Font* default_font = nullptr;

};

struct input {

    static inline Mouse* const mouse = new Mouse();

};

}

