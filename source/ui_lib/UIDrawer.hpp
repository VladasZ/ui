//
//  UIDrawer.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/5/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include "Rect.hpp"
#include "Mouse.hpp"
#include "Color.hpp"
#include "Image.hpp"

namespace ui {

class UIDrawer {

public:

    Size screen_resolution;

    virtual ~UIDrawer();

    virtual void fill_rect(const Rect&, const Color&) = 0;
    virtual void draw_image_in_rect(Image*, const Rect&) = 0;

#ifdef UI_DESKTOP
    virtual void set_cursor_mode(Mouse::CursorMode) = 0;
#endif

};
}
