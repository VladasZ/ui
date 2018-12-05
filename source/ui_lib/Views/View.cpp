//
//  View.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/5/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#include <iostream>

#include "ui.hpp"
#include "View.hpp"

using namespace std;
using namespace ui;

View::View(const Rect& rect) : _frame(rect), _absolute_frame(rect) { }

View::~View() {
	for (auto view : _subviews)
		delete view;
}

void View::add_subview(View* view) {
	view->_superview = this;
	view->_calculate_absolute_frame();
	_subviews.push_back(view);
}

void View::draw() {
	ui::config::drawer()->draw_rect(_absolute_frame);
	for (auto view : _subviews)
		view->draw();
}

void View::_calculate_absolute_frame() {
	_absolute_frame = _frame;
	if (_superview)
		_absolute_frame.origin += _superview->_absolute_frame.origin;
}
