//
//  View.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/5/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#include <iostream>
#include <algorithm>

#include "ui.hpp"
#include "View.hpp"
#include "Drawer.hpp"

using namespace std;
using namespace ui;

View::View(const Rect& rect) : _frame(rect) {

}

View::~View() {
	for (auto view : _subviews)
		delete view;
}

void View::add_subview(View* view) {
	view->_superview = this;
	_subviews.push_back(view);
}

void View::set_frame(const Rect& frame) {
	_frame = frame;
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

void View::draw() {

	if (_needs_layout) {
		_layout();
		_needs_layout = false;
	}

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
