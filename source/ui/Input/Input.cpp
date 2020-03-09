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

//#define LOG_TOUCHES

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

void Input::process_touch_event(Touch* touch) {

    if (!_views_to_subscribe.empty()) {
        cu::array::append(_subscribed_views, _views_to_subscribe);
        _views_to_subscribe.clear();
    }

    if (!_resizable_to_subscribe.empty()) {
        cu::array::append(_resizable, _resizable_to_subscribe);
        _resizable_to_subscribe.clear();
    }

    if (!_views_to_unsubscribe.empty()) {
        cu::array::remove_from(_subscribed_views, _views_to_unsubscribe);
        _views_to_unsubscribe.clear();
    }

    if (!_resizable_to_unsubscribe.empty()) {
        cu::array::remove_from(_resizable, _resizable_to_unsubscribe);
        _resizable_to_unsubscribe.clear();
    }

    on_touch(touch);

#ifdef LOG_TOUCHES
    Separator;
    Log(touch);
    Log(touch->to_string());
    //on_touch(touch);
    Log("lageza");
#endif



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
                return;
            }
        }
    }

    if (touch->is_began()) {
        for (auto view : _subscribed_views) {
            if (view->_absolute_frame.contains(touch->location) && view->is_visible()) {
                touch->location -= view->_absolute_frame.origin;
                view->_touch_id = touch->id;
                Log("Inputovka");
                view->on_touch(touch);
                return;
            }
        }
    }

    if (touch->is_ended()) {
        for (auto view : _subscribed_views) {
            if (view->_touch_id == touch->id) {
                touch->location -= view->_absolute_frame.origin;
                view->_touch_id = 0;
                view->on_touch(touch);
#ifndef MOUSE
                delete touch;
#endif
                return;
            }
        }
    }

    on_free_touch(touch);

}

void Input::subscribe_view(View* view) {
    _views_to_subscribe.push_back(view);
}

void Input::subscribe_resizable(View* view) {
    _resizable_to_subscribe.push_back(view);
}

void Input::unsubscribe_view(View* view) {
    _views_to_unsubscribe.push_back(view);
}

void Input::unsubscribe_resizable(View* view) {
    _resizable_to_unsubscribe.push_back(view);
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

    on_hover_moved(position);
    ui::config::drawer()->set_cursor_mode(Mouse::CursorMode::Arrow);
}

#endif
