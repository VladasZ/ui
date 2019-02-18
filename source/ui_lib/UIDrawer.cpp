//
//  UIDrawer.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/5/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#include "UIDrawer.hpp"

using namespace ui;

const Rect UIDrawer::_convert_rect(const Rect& rect) {
    return rect;
}

void UIDrawer::fill_rect(const Rect& rect, const Color& color) {
    _fill_rect(_convert_rect(rect), color);
}
