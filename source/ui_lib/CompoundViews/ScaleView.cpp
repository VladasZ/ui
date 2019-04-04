//
//  ScaleView.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 4/4/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#include "ui.hpp"
#include "ScaleView.hpp"
#include "PathData.hpp"
#include "UIDrawer.hpp"

using namespace ui;

ScaleView::ScaleView(size_t count) : _count(count) {

}

size_t ScaleView::count() const {
    return _count;
}

void ScaleView::_layout() {
    View::_layout();
    _create_lines();
}

void ScaleView::_draw() {
    View::_draw();
    ui::config::drawer()->draw_path_in_rect(_path, _absolute_frame);
}

void ScaleView::_create_lines() {
    if (_path)
        delete _path;

    gm::Path* path = new gm::Path();
    path->draw_mode = gm::Path::DrawMode::Lines;

    const float delta = _frame.size.width / _count;

    for (size_t i = 0; i < _count; i++) {
        path->add_point({ delta * i,                  0 });
        path->add_point({ delta * i, _frame.size.height });
    }

    _path = ui::config::drawer()->initialize_path_data(path, gm::Color::white);


}

