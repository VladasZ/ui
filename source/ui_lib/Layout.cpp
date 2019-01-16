//
//  Layout.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 1/11/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#include "View.hpp"
#include "Layout.hpp"

using namespace ui;

Layout::Layout(Anchor anchor, float value, View* anchor_view) : _value(value), _anchor(anchor), _anchor_view(anchor_view) {

}

void Layout::_layout_view(View* view) const {

    if (_anchor_view == nullptr) {

        const Rect& super_frame = view->_superview->_frame;
        Rect& frame = view->_frame;

        auto value = static_cast<uint64_t>(_anchor);

        if (value & static_cast<uint64_t>(Anchor::CenterH))
            frame.origin.x = super_frame.size.width / 2 - frame.size.width / 2 + _value;

        if (value & static_cast<uint64_t>(Anchor::CenterV))
            frame.origin.y = super_frame.size.height / 2 - frame.size.height / 2 + _value;

        if (value & static_cast<uint64_t>(Anchor::Bottom))
            frame.size.height = super_frame.size.height - frame.origin.y - _value;

        if (value & static_cast<uint64_t>(Anchor::Right))
            frame.size.width = super_frame.size.width - frame.origin.x - _value;

        if (value & static_cast<uint64_t>(Anchor::Top)) {
            frame.size.height += frame.origin.y - _value;
            frame.origin.y = _value;
        }

        if (value & static_cast<uint64_t>(Anchor::Left)) {
            frame.size.width += frame.origin.x - _value;
            frame.origin.x = _value;
        }

        view->_calculate_absolute_frame();

        return;
    }
}
