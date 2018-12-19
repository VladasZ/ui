//
//  Drawer.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/5/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include "Rect.hpp"
#include "Mouse.hpp"
#include "Color.hpp"

namespace ui {

class Drawer {
    virtual void _draw_rect(const Rect& rect) = 0;
    virtual void _fill_rect(const Rect& rect, const Color& color) = 0;
    virtual const Rect _convert_rect(const Rect& rect);

public:
    virtual ~Drawer() { }

    Size screen_resolution;
    void draw_rect(const Rect& rect);
    void fill_rect(const Rect& rect, const Color& color);

#ifdef UI_DESKTOP
private:
    virtual void _set_cursor_mode(Mouse::CursorMode cursor_mode) = 0;
public:
    virtual void set_cursor_mode(Mouse::CursorMode cursor_mode);
#endif

};
}
