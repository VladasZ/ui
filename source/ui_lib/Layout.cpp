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

Layout::Layout(Edge edge, float value, View* anchor) : _value(value), _edge(edge), _anchor(anchor) {

}

void Layout::_layout_view(View* view) const {

    if (_anchor == nullptr) {

        if (_edge == Edge::None)
            return;

        const Rect& super_frame = view->_superview->_frame;
        Rect& frame = view->_frame;

        auto value = static_cast<uint64_t>(_edge);

//        if (value & static_cast<uint64_t>(Edge::Bottom))
//            size.height = point.y - origin.y;

//        if (value & static_cast<uint64_t>(Edge::Right))
//            size.width = point.x - origin.x;

//        if (value & static_cast<uint64_t>(Edge::Top)) {
//            size.height += origin.y - point.y;
//            origin.y = point.y;
//        }

//        if (value & static_cast<uint64_t>(Edge::Left)) {
//            size.width += origin.x - point.x;
//            origin.x = point.x;
//        }

        if (value & static_cast<uint64_t>(Edge::Bottom))
            frame.size.height = super_frame.size.height - frame.origin.y - _value;

        if (value & static_cast<uint64_t>(Edge::Right)) {

        }

        if (value & static_cast<uint64_t>(Edge::Top)) {

        }

        if (value & static_cast<uint64_t>(Edge::Left)) {

        }

        if (value & static_cast<uint64_t>(Edge::CenterH)) {

        }

        if (value & static_cast<uint64_t>(Edge::CenterV)) {

        }

        view->_calculate_absolute_frame();

        return;
    }
}
