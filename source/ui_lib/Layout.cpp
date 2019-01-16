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

static uint64_t anchor_horisontal_elements(const Anchor anchor) {
    return static_cast<uint64_t>(anchor) & static_cast<uint64_t>(Anchor::_Horisontal);
}

static uint64_t anchor_vertical_elements(const Anchor anchor) {
    return static_cast<uint64_t>(anchor) & static_cast<uint64_t>(Anchor::_Vertical);
}

Layout::Layout(Anchor anchor, float value, View* anchor_view) : _value(value), _anchor(anchor), _anchor_view(anchor_view) {

}

void Layout::_layout_view(View* view) const {

    if (_anchor_view == nullptr) {

        const Rect& super_frame = view->_superview->_frame;
        Rect& frame = view->_frame;

        auto hor_anchor  = anchor_horisontal_elements(_anchor);
        auto vert_anchor = anchor_vertical_elements(_anchor);

        if (hor_anchor)
            _layout_one_dimension(frame.origin.x, frame.size.width, super_frame.size.width, static_cast<OneDimensionAnchor>(hor_anchor));

        if (vert_anchor)
            _layout_one_dimension(frame.origin.y, frame.size.height, super_frame.size.height, static_cast<OneDimensionAnchor>(vert_anchor));

        view->_calculate_absolute_frame();

        return;
    }
}

void Layout::_layout_one_dimension(float& origin, float& size, const float& space_size, OneDimensionAnchor anchor) const {
    if (anchor & OneDimensionAnchor::Center)
        _layout_center(origin, size, space_size);

    if (anchor & OneDimensionAnchor::Origin)
        _layout_origin(origin, size);

    if (anchor & OneDimensionAnchor::Length)
        _layout_length(origin, size, space_size);
}

void Layout::_layout_center(float& origin, const float& size, const float& space_size) const {
    origin = space_size / 2 - size / 2 + _value;
}

void Layout::_layout_length(const float& origin, float& size, const float& space_size) const {
    size = space_size - origin - _value;
}

void Layout::_layout_origin(float& origin, float& size) const {
    size += origin - _value;
    origin = _value;
}
