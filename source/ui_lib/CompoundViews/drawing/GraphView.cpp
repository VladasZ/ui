//
//  GraphView.сpp
//  ui
//
//  Created by Vladas Zakrevskis on 4/25/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#include "GraphView.hpp"

using namespace ui;

GraphView::~GraphView() {
    delete _path;
}

size_t GraphView::points_size() const {
    return _points_size;
}

void GraphView::set_points_size(size_t size) {
    _points_size = size;
    _recalculate_graph();
}

float GraphView::multiplier() const {
    return _multiplier;
}

void GraphView::set_multiplier(float multiplier) {
    _multiplier = multiplier;
    _recalculate_graph();
}

void GraphView::add_point(float point) {
    if (_points.size() > _points_size)
        reset();
    _points.push_back(point);
    _path->add_point({ _points.size() * _delta(), point * _multiplier });
    _drawing_view->remove_all_paths();
    _drawing_view->add_path(_path, color);
}

void GraphView::reset() {
    _path->clear();
    _points.clear();
    _drawing_view->remove_all_paths();
}

float GraphView::_delta() const {
    return _frame.size.width / _points_size;
}

void GraphView::_setup() {
    _path = new gm::Path();
    add_subview(_drawing_view = new DrawingView());
}

void GraphView::_layout() {
    View::_layout();
    _drawing_view->set_frame(_frame.with_zero_origin());
    _recalculate_graph();
}

void GraphView::_recalculate_graph() {
    _path->clear();
    for (size_t i = 0; i < _points.size(); i++)
        _path->add_point({ i * _delta(), _points[i] * _multiplier });
    _drawing_view->remove_all_paths();
    _drawing_view->add_path(_path, color);
}
