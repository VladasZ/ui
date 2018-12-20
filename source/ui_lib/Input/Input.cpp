//
//  Input.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/18/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#include "ui.hpp"

#include "Mouse.hpp"
#include "Input.hpp"
#include "Window.hpp"

using namespace ui;

static Mouse::CursorMode window_edge_to_mouse_cursor_mode(Rect::Edge edge) {
    auto int_value = static_cast<int>(edge);

    if (int_value < static_cast<int>(Rect::Edge::Left))
        return Mouse::CursorMode::VResize;

    if (int_value == static_cast<int>(Rect::Edge::Left) ||
        int_value == static_cast<int>(Rect::Edge::Right))
        return Mouse::CursorMode::HResize;

    return Mouse::CursorMode::Drag;
}

void Input::touch_event(Touch* touch) {

    if (touch->is_began()) {
        _touches.push_back(touch);
    };

    if (touch->is_moved()) {

    }


}

#ifdef UI_DESKTOP
void Input::hover_moved(const Point& position) {

    for (auto window : _windows) {
        auto edge = window->get_edge(position);
        if (edge != Rect::Edge::None) {
            ui::config::drawer()->set_cursor_mode(window_edge_to_mouse_cursor_mode(edge));
            return;
        }
    }

    ui::config::drawer()->set_cursor_mode(Mouse::CursorMode::Arrow);
}
#endif
