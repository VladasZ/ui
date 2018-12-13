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

void View::set_origin(const Point& origin) {
	_frame.origin = origin;
	_calculate_absolute_frame();
}

void View::set_center(const Point& center) {
	_frame.origin.x = center.x - _frame.size.width  / 2;
	_frame.origin.y = center.y - _frame.size.height / 2;
	_calculate_absolute_frame();
}

void View::draw() {
	ui::config::drawer()->fill_rect(_absolute_frame, color);
	for (auto view : _subviews)
		view->draw();
}

View::Edge View::get_edge(const Point& point) const {

	uint8_t edge = 0;

	if (!_absolute_frame.contains_with_edge(point, EdgeInfo::width / 2))
		return static_cast<Edge>(edge);

	if (point.x >= _edge_info.left_min && point.x <= _edge_info.left_max)
		edge += static_cast<uint8_t>(Edge::Left);

	if (point.x >= _edge_info.right_min && point.x <= _edge_info.right_max)
		edge += static_cast<uint8_t>(Edge::Right);

	if (point.y >= _edge_info.top_min && point.y <= _edge_info.top_max)
		edge += static_cast<uint8_t>(Edge::Top);

	if (point.y >= _edge_info.bottom_min && point.y <= _edge_info.bottom_max)
		edge += static_cast<uint8_t>(Edge::Bottom);

	return static_cast<Edge>(edge);
}

void View::_calculate_absolute_frame() {
	_absolute_frame = _frame;

	if (_superview)
		_absolute_frame.origin += _superview->_absolute_frame.origin;

	_edge_info.left_min   = _absolute_frame.origin.x - EdgeInfo::width / 2;
	_edge_info.left_max   = _absolute_frame.origin.x + EdgeInfo::width / 2;

	_edge_info.right_min  = _absolute_frame.origin.x + _absolute_frame.size.width - EdgeInfo::width / 2;
	_edge_info.right_max  = _absolute_frame.origin.x + _absolute_frame.size.width + EdgeInfo::width / 2;

	_edge_info.top_min    = _absolute_frame.origin.y - EdgeInfo::width / 2;
	_edge_info.top_max    = _absolute_frame.origin.y + EdgeInfo::width / 2;

	_edge_info.bottom_min = _absolute_frame.origin.y + _absolute_frame.size.height - EdgeInfo::width / 2;
	_edge_info.bottom_max = _absolute_frame.origin.y + _absolute_frame.size.height + EdgeInfo::width / 2;
}
