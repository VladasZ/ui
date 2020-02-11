//
//  Input.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 18/12/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#include <algorithm>

#include "ui.hpp"

#include "Log.hpp"
#include "View.hpp"
#include "Touch.hpp"
#include "Mouse.hpp"
#include "Input.hpp"
#include "UIDrawer.hpp"
#include "ArrayUtils.hpp"
#include "ViewResizer.hpp"

using namespace ui;
using namespace gm;

#ifdef DESKTOP_BUILD
static Mouse::CursorMode window_edge_to_mouse_cursor_mode(Edge edge) {
    auto int_value = static_cast<int>(edge);

    if (int_value < static_cast<int>(Edge::Left)) {
        return Mouse::CursorMode::VResize;
    }

    if (int_value == static_cast<int>(Edge::Left) ||
        int_value == static_cast<int>(Edge::Right)) {
        return Mouse::CursorMode::HResize;
    }

    return Mouse::CursorMode::Drag;
}
#endif

void Input::_unsubscribe_view(View* view) {
    cu::array::remove(_subscribed_views, view);
}

void Input::_unsubscribe_resizable(View* view) {
    cu::array::remove(_resizable, view);
}

void Input::process_touch_event(Touch* touch) {

    on_touch(touch);

#ifdef LOG_TOUCHES
    Log(touch->to_string());
#endif

#ifdef MOUSE
    if (touch->is_moved() && touch->is_right_click()) {
        on_right_button_drag(touch);
    }
#endif

    if (touch->is_moved()) {
        for (auto view : _subscribed_views) {
            if (view->_touch_id == touch->id) {
                touch->location -= view->_absolute_frame.origin;
                view->on_touch(touch);
                break;
            }
        }
    }
    else if (touch->is_began()) {
        for (auto view : _subscribed_views) {
            if (view->_absolute_frame.contains(touch->location)) {
                touch->location -= view->_absolute_frame.origin;
                view->_touch_id = touch->id;
                view->on_touch(touch);
                break;
            }
        }
    }
    else /*if (touch->is_ended())*/ {
        for (auto view : _subscribed_views) {
            if (view->_touch_id == touch->id) {
                touch->location -= view->_absolute_frame.origin;
                view->_touch_id = 0;
                view->on_touch(touch);
                break;
            }
        }
#ifndef MOUSE
        delete touch;
#endif
    }

    if (_resizing_view) {
        if (touch->is_ended()) {
            _resizing_view = nullptr;
            return;
        }
        _resizing_view->_resizer->on_touch(touch);
    }

    for (auto window : _resizable) {
        if (window->_absolute_frame.contains_with_edge(touch->location, ViewResizer::EdgeInfo::width)) {
            _resizing_view = window;
            window->_resizer->on_touch(touch);
            return;
        }
    }
}

#ifdef DESKTOP_BUILD
void Input::hover_moved(const Point& position) {

    for (auto view : _resizable) {
        auto edge = view->_resizer->get_edge(position);
        if (edge != Edge::None) {
            ui::config::drawer()->set_cursor_mode(window_edge_to_mouse_cursor_mode(edge));
            return;
        }
    }

    ui::config::drawer()->set_cursor_mode(Mouse::CursorMode::Arrow);
}
#endif
