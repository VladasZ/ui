//
//  ui.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/5/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include "Mouse.hpp"
#include "Drawer.hpp"

namespace ui {

struct config {

    static Drawer* drawer();
    static void set_drawer(Drawer* drawer);

};

struct input {

    static inline Mouse* const mouse = new Mouse();

};

}

