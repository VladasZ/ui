//
//  View.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/5/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#include <algorithm>

#include "ui.hpp"
#include "View.hpp"
#include "Input.hpp"
#include "UIDrawer.hpp"

using namespace ui;
using namespace gm;

View::View(const Rect& rect) : _frame(rect) {

}

View::~View() {
    if (_user_interaction_enabled)
        Input::_unsubscribe_view(this);
    for (auto view : _subviews)
        delete view;
}

void View::add_subview(View* view) {
    view->_superview = this;
    _subviews.push_back(view);
    view->_setup();
}

void View::add_subview(std::initializer_list<View*> views) {
    for (auto view : views)
        add_subview(view);
}

void View::remove_all_subviews() {
    for (auto view : _subviews)
        delete view;
    _subviews.clear();
}

Rect View::frame() const {
    return _frame;
}

View* View::superview() const {
    return _superview;
}

void View::set_frame(const Rect& frame) {
    _frame = frame;
    _needs_layout = true;
}

void View::edit_frame(std::function<void(Rect&)> edit) {
    edit(_frame);
    _needs_layout = true;
}

void View::set_origin(const Point& origin) {
    _frame.origin = origin;
    _needs_layout = true;
}

void View::set_center(const Point& center) {
    _frame.set_center(center);
    _needs_layout = true;
}

Point View::global_point_lo_local(const Point& point) const {
    return point - _absolute_frame.origin;
}

bool View::contains_global_point(const Point& point) const {
    return _absolute_frame.contains(point);
}

void View::_draw() {
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
    ui::config::drawer()->draw_rect(_absolute_frame, gm::Color::turquoise);
#endif
}

void View::_draw_subviews() {
    for (auto view : _subviews)
        view->_draw();
}

void View::_layout() {
    _calculate_absolute_frame();
    _layout_subviews();
}

void View::_calculate_absolute_frame() {
    _absolute_frame = _frame;
    if (_superview)
        _absolute_frame.origin += _superview->_absolute_frame.origin;
}

void View::_layout_subviews() {
    for (auto subview : _subviews)
        subview->_layout();
}

void View::enable_user_interaction() {
    if (_user_interaction_enabled)
        return;
    _user_interaction_enabled = true;
    Input::_subscribed_views.push_back(this);
}

void View::disable_user_interaction() {
    if (!_user_interaction_enabled)
        return;
    _user_interaction_enabled = false;
    Input::_unsubscribe_view(this);
}

View* View::dummy(const Rect& frame) {
    auto view = new View(frame);
    view->background_color = Color::random();
    return view;
}

