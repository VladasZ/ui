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
    virtual void _fill_rect(const Rect&, const Color&) = 0;
    virtual const Rect _convert_rect(const Rect&);

public:
    virtual ~UIDrawer() { }

    Size screen_resolution;
    void fill_rect(const Rect&, const Color&);

    virtual Image::Drawer* init_image_drawer(Image*) = 0;

#ifdef UI_DESKTOP
    virtual void set_cursor_mode(Mouse::CursorMode) = 0;
#endif

};
}
