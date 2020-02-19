//
//  View.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/5/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#include <algorithm>

#include "ui.hpp"
#include "Log.hpp"
#include "View.hpp"
#include "Input.hpp"
#include "ArrayUtils.hpp"
#include "ViewResizer.hpp"

using namespace ui;
using namespace gm;


View::View(const Rect& rect) : _frame(rect) { }

View::~View() {
    for (auto view : _subviews) delete view;
    disable_touch();
    disable_resize();
}

void View::add_subview(View* view) {
    view->_superview = this;
    _subviews.push_back(view);
    view->_setup();
}

void View::add_subviews(std::initializer_list<View*> views) {
    for (auto view : views) add_subview(view);
}

void View::remove_all_subviews() {
    for (auto view : _subviews) delete view;
    _subviews.clear();
}

void View::remove_from_superview() {
    cu::array::remove(_superview->_subviews, this);
    delete this;
}

View* View::superview() const {
    return _superview;
}

const Rect& View::frame() const {
    return _frame;
}

Rect& View::edit_frame() {
    _needs_layout = true;
    return _frame;
}

const Rect& View::absolute_frame() const {
    return _absolute_frame;
}

void View::set_center(const Point& center) {
    _frame.set_center(center);
    _needs_layout = true;
}

void View::place_b(float height) {
    edit_frame() =
            { 0,
              _superview->frame().size.height - height,
              _superview->frame().size.width,
              height
            };
}

void View::place_br(const Size& size) {
    edit_frame() =
            { _superview->frame().size.width - size.width,
              _superview->frame().size.height - size.height,
              size.width,
              size.height
            };
}

void View::place_bl(const Size& size) {
    edit_frame() =
            { 0,
              _superview->frame().size.height - size.height,
              size.width,
              size.height
            };
}

void View::place_tr(const Size& size) {
    edit_frame() =
            { _superview->frame().size.width - size.width,
              0,
              size.width,
              size.height
            };
}

Point View::global_point_lo_local(const Point& point) const {
    return point - _absolute_frame.origin;
}

bool View::contains_global_point(const Point& point) const {
    return _absolute_frame.contains(point);
}

void View::_draw() {
    if (is_hidden) return;
    _layout();
    _draw_rect();
    if (!_subviews.empty()) {
        _draw_subviews();
    }
}

void View::_draw_rect() {
    if (!background_color.is_clear()) {
        ui::config::drawer()->fill_rect(_absolute_frame, background_color);
    }
#ifdef DRAW_DEBUG_FRAMES
    if (draw_debug_frame) {
        ui::config::drawer()->draw_rect(_absolute_frame, Color::turquoise);
    }
#endif
}

void View::_draw_subviews() {
    for (auto view : _subviews) {
        view->_draw();
    }
}

void View::_layout() {
    _calculate_absolute_frame();
    _layout_subviews();
}

void View::_calculate_absolute_frame() {
    _absolute_frame = _frame;
    if (_superview) {
        _absolute_frame.origin += _superview->_absolute_frame.origin;
    }
    if (_resize_enabled) {
        _resizer->update_edge_info();
    }
}

void View::_layout_subviews() {
    for (auto subview : _subviews) subview->_layout();
}

void View::enable_touch() {
    if (_touch_enabled) return;
    _touch_enabled = true;
    Input::_subscribed_views.push_back(this);
}

void View::disable_touch() {
    if (!_touch_enabled) return;
    _touch_enabled = false;
    Input::_unsubscribe_view(this);
}

void View::enable_resize() {
    if (_resize_enabled) return;
    _resize_enabled = true;
    _resizer = new ViewResizer(_frame, _absolute_frame, _needs_layout);
    Input::_resizable.push_back(this);
}

void View::disable_resize() {
    if (!_resize_enabled) return;
    _resize_enabled = false;
    delete _resizer;
    _resizer = nullptr;
}

View* View::dummy(const Rect& frame) {
    auto view = new View(frame);
    view->background_color = Color::random();
    return view;
}
