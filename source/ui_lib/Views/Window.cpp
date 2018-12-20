//
//  Window.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/19/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#include <iostream>
using namespace std; //REMOVE

#include <algorithm>

#include "Input.hpp"
#include "Window.hpp"

using namespace ui;

Window::Window(const Rect& rect) : View(rect) {
    Input::_windows.push_back(this);
}

Window::~Window() {
    Input::_unsubscribe_window(this);
}

void Window::touch_event(Touch* touch) {
    cout << "touch location: " << touch->location.to_string() << endl;
    _frame.set_edge(_current_edge, touch->location);
    cout << "new frame: " << _frame.to_string() << endl;
    _needs_layout = true;
}

Rect::Edge Window::get_edge(const Point& point) {

    using Edge = Rect::Edge;

    uint8_t edge = 0;

    if (!_absolute_frame.contains_with_edge(point, EdgeInfo::width / 2))
        return Edge::None;

    if (point.x >= _edge_info.left_min && point.x <= _edge_info.left_max)
        edge += static_cast<uint8_t>(Edge::Left);

    if (point.x >= _edge_info.right_min && point.x <= _edge_info.right_max)
        edge += static_cast<uint8_t>(Edge::Right);

    if (point.y >= _edge_info.top_min && point.y <= _edge_info.top_max)
        edge += static_cast<uint8_t>(Edge::Top);

    if (point.y >= _edge_info.bottom_min && point.y <= _edge_info.bottom_max)
        edge += static_cast<uint8_t>(Edge::Bottom);

    _current_edge = static_cast<Edge>(edge);

    return _current_edge;
}

void Window::_layout() {
    View::_layout();

    _edge_info.left_min   = _absolute_frame.origin.x - EdgeInfo::width / 2;
    _edge_info.left_max   = _absolute_frame.origin.x + EdgeInfo::width / 2;

    _edge_info.right_min  = _absolute_frame.origin.x + _absolute_frame.size.width - EdgeInfo::width / 2;
    _edge_info.right_max  = _absolute_frame.origin.x + _absolute_frame.size.width + EdgeInfo::width / 2;

    _edge_info.top_min    = _absolute_frame.origin.y - EdgeInfo::width / 2;
    _edge_info.top_max    = _absolute_frame.origin.y + EdgeInfo::width / 2;

    _edge_info.bottom_min = _absolute_frame.origin.y + _absolute_frame.size.height - EdgeInfo::width / 2;
    _edge_info.bottom_max = _absolute_frame.origin.y + _absolute_frame.size.height + EdgeInfo::width / 2;
}
