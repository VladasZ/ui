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
#include "Drawer.hpp"

using namespace ui;

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
	_frame.origin.x = center.x - _frame.size.width  / 2;
	_frame.origin.y = center.y - _frame.size.height / 2;
	_needs_layout = true;
}

Point View::global_point_lo_local(const Point& point) const {
    return point - _absolute_frame.origin;
}

bool View::contains_global_point(const Point& point) const {
    return _absolute_frame.contains(point);
}

void View::draw() {

	if (_needs_layout) {
		_layout();
		_needs_layout = false;
	}

    if (!_frame.size.is_negative())
        ui::config::drawer()->fill_rect(_absolute_frame, color);

	for (auto view : _subviews)
		view->draw();
}

void View::_layout() {
	_absolute_frame = _frame;

	if (_superview)
		_absolute_frame.origin += _superview->_absolute_frame.origin;

	for (auto subview : _subviews)
		subview->_layout();
}

void View::touch_event(Touch *touch) {
    switch (touch->event) {
    case Touch::Event::Began:
        _touches.push_back(touch);
        break;
    case Touch::Event::Moved:
        break;
    case Touch::Event::Ended:
        auto iter = std::find(_touches.begin(), _touches.end(), touch);
        if (iter == _touches.end())
            return;
        _touches.erase(iter);
        break;
    }
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
