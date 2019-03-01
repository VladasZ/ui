//
//  Input.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/18/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#include <algorithm>

#include "ui.hpp"

#include "Touch.hpp"
#include "Mouse.hpp"
#include "Input.hpp"
#include "Window.hpp"
#include "UIDrawer.hpp"

using namespace ui;

static std::function<void(Touch*)> _on_touch_event_proc;

static Mouse::CursorMode window_edge_to_mouse_cursor_mode(Edge edge) {
    auto int_value = static_cast<int>(edge);

    if (int_value < static_cast<int>(Edge::Left))
        return Mouse::CursorMode::VResize;

    if (int_value == static_cast<int>(Edge::Left) ||
        int_value == static_cast<int>(Edge::Right))
        return Mouse::CursorMode::HResize;

    return Mouse::CursorMode::Drag;
}

void Input::_unsubscribe_view(View* view) {
    auto iter = std::find(_subscribed_views.begin(), _subscribed_views.end(), view);
    if (iter == _subscribed_views.end())
        return;
    _subscribed_views.erase(iter);
}

void Input::_unsubscribe_window(Window* view) {
    auto iter = std::find(_windows.begin(), _windows.end(), view);
    if (iter == _windows.end())
        return;
    _windows.erase(iter);
}

void Input::touch_event(Touch* touch) {

    if (_on_touch_event_proc)
        _on_touch_event_proc(touch);

    for (auto view : _subscribed_views) {
        if (view->_absolute_frame.contains(touch->location)) {
            touch->location -= view->_absolute_frame.origin;
            view->touch_event(touch);
            return;
        }
    }

    if (_resizing_window) {
        if (touch->is_ended()) {
            _resizing_window = nullptr;
            return;
        }
        _resizing_window->touch_event(touch);
    }

    for (auto window : _windows) {
        if (window->_absolute_frame.contains_with_edge(touch->location, Window::EdgeInfo::width)) {
            _resizing_window = window;
            window->touch_event(touch);
            return;
        }
    }
}

void Input::on_touch_event(std::function<void(Touch*)> proc) {
    _on_touch_event_proc = proc;
}

#if DESKTOP_BUILD
void Input::hover_moved(const Point& position) {

    for (auto window : _windows) {
        auto edge = window->get_edge(position);
        if (edge != Edge::None) {
            ui::config::drawer()->set_cursor_mode(window_edge_to_mouse_cursor_mode(edge));
            return;
        }
    }

    ui::config::drawer()->set_cursor_mode(Mouse::CursorMode::Arrow);
}
#endif
