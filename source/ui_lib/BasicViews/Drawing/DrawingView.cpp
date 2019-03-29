//
//  DrawingView.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 4/28/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#include "ui.hpp"
#include "UIDrawer.hpp"
#include "DrawingView.hpp"

using namespace ui;


DrawingView::~DrawingView() {
    for (auto path : _paths)
        delete path;
}

void DrawingView::add_path(gm::Path* path) {
    _paths.push_back(ui::config::drawer()->initialize_path_data(path));
}

#include "Log.hpp"

void DrawingView::_draw() {
    View::_draw();
    for (auto path : _paths) {
        ui::config::drawer()->draw_path_in_rect(path, _absolute_frame, path->color());
       // Info(path->path()->to_string());
    }
}
