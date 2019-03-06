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

    gm::Size screen_resolution;

    virtual ~UIDrawer();

    virtual void fill_rect(const gm::Rect&, const gm::Color&) = 0;
    virtual void draw_image_in_rect(Image*, const gm::Rect&) = 0;

#if DESKTOP_BUILD
    virtual void set_cursor_mode(Mouse::CursorMode) = 0;
#endif

};
}
