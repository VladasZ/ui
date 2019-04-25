//
//  ChartView.сpp
//  ui
//
//  Created by Vladas Zakrevskis on 4/25/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#include "ChartView.hpp"

using namespace ui;

size_t ChartView::size() const {
    return _graphs.size();
}

void ChartView::set_size(size_t size) {
    remove_all_subviews();
    _graphs.clear();
    for (size_t i = 0; i < size; i++) {
        auto graph = new DrawingView();
        _graphs.push_back(graph);
        add_subview(graph);
    }
}

void ChartView::_setup() {
    set_size(1);
}

void ChartView::_layout() {
    View::_layout();
    for (auto graph : _graphs)
        graph->set_frame(_frame.with_zero_origin());
}
