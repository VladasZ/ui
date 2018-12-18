//
//  Drawer.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/5/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#include "Drawer.hpp"

using namespace ui;

const Rect Drawer::_convert_rect(const Rect& rect) {
	return rect;
}

void Drawer::draw_rect(const Rect& rect) {
	_draw_rect(_convert_rect(rect));
}

void Drawer::fill_rect(const Rect& rect, const Color& color) {
	_fill_rect(_convert_rect(rect), color);
}

void Drawer::set_cursor_mode(CursorMode cursor_mode) {
    //_set_cursor_mode(cursor_mode);
}
