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

//enum class Edge : uint8_t {
//    Top         = 0b00000001,
//    Bottom      = 0b00000010,
//    Left        = 0b00000100,
//    Right       = 0b00001000,
//    TopLeft     = Top    | Left,
//    TopRight    = Top    | Right,
//    BottomLeft  = Bottom | Left,
//    BottomRight = Bottom | Right,
//    None        = 0
//};

//enum class CursorMode {
//    Arrow,
//    Text,
//    Drag,
//    HResize,
//    VResize
//};

static Mouse::CursorMode window_edge_to_mouse_cursor_mode(Window::Edge edge) {
    auto int_value = static_cast<int>(edge);

    if (int_value < static_cast<int>(Window::Edge::Left))
        return Mouse::CursorMode::VResize;

    if (int_value == static_cast<int>(Window::Edge::Left) ||
		int_value == static_cast<int>(Window::Edge::Right))
        return Mouse::CursorMode::HResize;

    return Mouse::CursorMode::Drag;
}

void Input::cursor_moved(const Point& position) {

    for (auto window : _windows) {
        auto edge = window->get_edge(position);
        if (edge != Window::Edge::None) {
            ui::config::drawer()->set_cursor_mode(window_edge_to_mouse_cursor_mode(edge));
            return;
        }
    }

    ui::config::drawer()->set_cursor_mode(Mouse::CursorMode::Arrow);
}
