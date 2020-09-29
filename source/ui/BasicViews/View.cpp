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
#include "FrameResizer.hpp"

using namespace ui;


View::View(const Rect& rect) : _frame(rect) { }

View::~View() {
    for (auto view : _subviews) delete view;
    disable_touch();
    disable_resize();
}

View* View::superview() const {
    return _superview;
}

const View::Array &View::subviews() const {
    return _subviews;
}

void View::add_subview(View* view) {
    view->_superview = this;
    _subviews.push_back(view);
    view->setup();
}

void View::remove_all_subviews() {
    for (auto view : _subviews) delete view;
    _subviews.clear();
}

void View::remove_from_superview() {
    cu::array::remove(_superview->_subviews, this);
    delete this;
}

void View::remove_last_subview() {
    delete _subviews.back();
    _subviews.pop_back();
}

const Rect& View::frame() const {
    return _frame;
}

Rect& View::edit_frame() {
    _needs_reposition = true;
    _needs_resize = true;
    for (auto view : _subviews) {
        view->_set_needs_reposition();
    }
    return _frame;
}

const Rect& View::absolute_frame() const {
    return _absolute_frame;
}

Float View::content_width() const {
    return std::max(_frame.size.width, content_size.width);
}

Float View::content_height() const {
    return std::max(_frame.size.height, content_size.height);
}

void View::set_center(const Point& center) {
    _frame.set_center(center);
    _set_needs_reposition();
}

void View::place_as_background() {
    edit_frame() = _superview->frame().with_zero_origin();
}

void View::place_at_center() {
    _frame.origin.x = _superview->content_width() / 2 - _frame.size.width  / 2;
    _frame.origin.y = _superview->content_height() / 2 - _frame.size.height / 2;
    _set_needs_reposition();
}

void View::center_vertically() {
    _frame.origin.y = _superview->content_height() / 2 - _frame.size.height / 2;
    _set_needs_reposition();
}

void View::center_horizontally() {
    _frame.origin.x = _superview->content_width() / 2 - _frame.size.width / 2;
    _set_needs_reposition();
}

void View::place_at_bottom(Float margin) {
    _frame.set_center(_superview->frame().center());
    _frame.origin.y = _superview->content_height() - _frame.size.height - margin;
    _set_needs_reposition();
}

void View::place_br(Float margin) {
    _frame.origin.x = _superview->frame().size.width  - _frame.size.width  - margin;
    _frame.origin.y = _superview->content_height() - _frame.size.height - margin;
    _set_needs_reposition();
}

void View::place_bl(Float margin) {
    _frame.origin.x = margin;
    _frame.origin.y = _superview->content_height() - _frame.size.height - margin;
    _set_needs_reposition();
}

void View::place_tr(Float margin) {
    _frame.origin.x = _superview->content_width() - _frame.size.width - margin;
    _frame.origin.y = margin;
    _set_needs_reposition();
}

void View::place_at_left_half() {
    _frame.origin = { };
    _frame.size = { _superview->frame().size.width / 2, _superview->frame().size.height };
    _set_needs_resize();
}

void View::place_at_right_half() {
    _frame.origin = { _superview->frame().size.width / 2, 0 };
    _frame.size = { _superview->frame().size.width / 2, _superview->frame().size.height };
    _set_needs_resize();
}

void View::place_at_top_half() {
    _frame = { 0,
               0,
               _superview->frame().size.width,
               _superview->frame().size.height / 2
    };
    _set_needs_resize();
}

void View::place_at_bottom_half() {
    _frame = { 0,
               _superview->frame().size.height / 2,
               _superview->frame().size.width,
               _superview->frame().size.height / 2
    };
    _set_needs_resize();
}

void View::stick_to(View* view, Edge edge, Float margin, Edge alignment) {

    const auto& target_frame = view->frame();

    _frame.set_center(target_frame.center());

    if (edge == Edge::Right) {
        _frame.origin.x = target_frame.max_x() + margin;
    }
    else if (edge == Edge::Left) {
        _frame.origin.x = target_frame.min_x() - margin - _frame.size.width;
    }
    else if (edge == Edge::Top) {
        _frame.origin.y = target_frame.min_y() - margin - _frame.size.height;
    }
    else if (edge == Edge::Bottom) {
        _frame.origin.y = target_frame.max_y() + margin;
    }
    else {
        Fatal("Invalid edge");
    }

    if (alignment == Edge::Center) {
        _set_needs_reposition();
        return;
    }

    if (alignment == Edge::Left) {
        _frame.origin.x = target_frame.origin.x;
    }
    else if (alignment == Edge::Right) {
        _frame.origin.x = target_frame.max_x() - _frame.size.width;
    }
    else if (alignment == Edge::Top) {
        _frame.origin.y = target_frame.origin.y;
    }
    else if (alignment == Edge::Bottom) {
        _frame.origin.y = target_frame.max_y() - _frame.size.height;
    }
    else {
        Fatal("Invalid alignment");
    }

    _set_needs_reposition();

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
    if (_needs_reposition) _calculate_absolute_frame();
    if (_needs_resize) layout();
    if (clips) {
        GL::scissor_begin(_absolute_frame);
    }
    _draw_rect();
    for (auto view : _subviews) {
        view->_draw();
    }
    if (clips) {
        GL::scissor_end();
    }
}

void View::_set_needs_resize() {
    _needs_resize = true;
    for (auto view : _subviews) {
        view->_set_needs_reposition();
    }
}

void View::_set_needs_reposition() {
    _needs_reposition = true;
    for (auto view : _subviews) {
        view->_set_needs_reposition();
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

void View::_calculate_absolute_frame() {
    _absolute_frame = _frame;
    if (_superview) {
        _absolute_frame.origin += _superview->_absolute_frame.origin + _superview->content_offset;
    }
    if (_resize_enabled) {
        _resizer->update_edge_info();
    }
}

void View::enable_touch() {
    if (_touch_enabled) return;
    _touch_enabled = true;
    Input::subscribe_view(this);
}

void View::disable_touch() {
    if (!_touch_enabled) return;
    Log << this;
    _touch_enabled = false;
    Input::unsubscribe_view(this);
}

void View::enable_resize() {
    if (_resize_enabled) return;
    _resize_enabled = true;
    static bool dummy = true;
    _resizer = new FrameResizer(_frame, _absolute_frame, dummy);
    Input::subscribe_resizable(this);
}

void View::disable_resize() {
    if (!_resize_enabled) return;
    _resize_enabled = false;
    delete _resizer;
    _resizer = nullptr;
    Input::unsubscribe_resizable(this);
}

View* View::dummy(const Rect& frame) {
    auto view = new View(frame);
    view->background_color = Color::random();
    return view;
}
