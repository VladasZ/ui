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

        if (value & static_cast<uint64_t>(Edge::Bottom)) {

        }

        if (value & static_cast<uint64_t>(Edge::Right)) {

        }

        if (value & static_cast<uint64_t>(Edge::Top)) {

        }

        if (value & static_cast<uint64_t>(Edge::Left)) {

        }

        view->_calculate_absolute_frame();

        return;
    }
}
