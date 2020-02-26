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
#include "GLWrapper.hpp"
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

void View::place_at_center() {
    _frame.origin.x = _superview->content_width() / 2 - _frame.size.width  / 2;
    _frame.origin.y = _superview->content_height() / 2 - _frame.size.height / 2;
}

void View::place_at_bottom(float margin) {
    _frame.set_center(_superview->frame().center());
    _frame.origin.y = _superview->content_height() - _frame.size.height - margin;
    _needs_layout = true;
}

void View::place_br(float margin) {
    _frame.origin.x = _superview->frame().size.width  - _frame.size.width  - margin;
    _frame.origin.y = _superview->content_height() - _frame.size.height - margin;
    _needs_layout = true;
}

void View::place_bl(float margin) {
    _frame.origin.x = margin;
    _frame.origin.y = _superview->content_height() - _frame.size.height - margin;
    _needs_layout = true;
}

void View::place_tr(float margin) {
    _frame.origin.x = _superview->content_width() - _frame.size.width - margin;
    _frame.origin.y = margin;
    _needs_layout = true;
}

float View::content_width() const {
    return std::max(_frame.size.width, content_size.width);
}

float View::content_height() const {
    return std::max(_frame.size.height, content_size.height);
}

void View::stick_to(View* view, Edge edge, float margin) {

    _frame.set_center(view->frame().center());

    if (edge == Edge::Right) {
        _frame.origin.x = view->frame().max_x() + margin;
    }
    else if (edge == gm::Edge::Left) {
        _frame.origin.x = view->frame().min_x() - margin - _frame.size.width;
    }
    else if (edge == gm::Edge::Top) {
        _frame.origin.y = view->frame().min_y() - margin - _frame.size.height;
    }
    else if (edge == gm::Edge::Bottom) {
        _frame.origin.y = view->frame().max_y() + margin;
    }

    _needs_layout = true;

}

Point View::global_point_lo_local(const Point& point) const {
    return point - _absolute_frame.origin;
}

bool View::contains_global_point(const Point& point) const {
    return _absolute_frame.contains(point);
}

bool View::is_visible() const {
    if (is_hidden) return false;
    if (_superview == nullptr) return true;

    auto super = _superview;

    while (super) {
        if (super->is_hidden) return false;
        super = super->superview();
    }

    return true;
}

void View::_draw() {
    if (is_hidden) return;
    _layout();
    _draw_rect();
    if (clips) {
        GL::scissor_begin(_absolute_frame);
    }
    if (!_subviews.empty()) {
        _draw_subviews();
    }
    if (clips) {
        GL::scissor_end();
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
        _absolute_frame.origin += _superview->_absolute_frame.origin + _superview->content_offset;
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
    Input::_unsubscribe_resizable(this);
}

View* View::dummy(const Rect& frame) {
    auto view = new View(frame);
    view->background_color = Color::random();
    return view;
}
