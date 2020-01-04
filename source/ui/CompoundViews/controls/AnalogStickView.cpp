//
//  AnalogStickView.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 3/12/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#ifndef DESKTOP_BUILD

#include "Log.hpp"
#include "Event.hpp"
#include "AnalogStickView.hpp"

using namespace ui;
using namespace gm;
using namespace std;

static const float SIZE = 140;
static const float OUTLINE_WIDTH = 10;
static const float STICK_VIEW_SIZE = SIZE / 2;

AnalogStickView::AnalogStickView() : DrawingView({ SIZE, SIZE }) {

}

void AnalogStickView::on_touch_moved(const Point& touch) {
    const auto max_lenght = _frame.size.height / 2;
    const auto center = _frame.size.center();
    
    Point vector = (touch - center).trimmed(max_lenght);
    
    direction_stick->set_center(vector + _frame.size.center());
    on_direction_change(vector * 0.1f);
}

void AnalogStickView::_setup() {
    
    enable_user_interaction();
    
    add_path(PointsPath::circle_with(_frame.size.center(), _frame.size.width),
             Color::black);

    add_path(PointsPath::circle_with(_frame.size.center(), _frame.size.width - OUTLINE_WIDTH),
             Color::white);

    direction_stick = new DrawingView({ STICK_VIEW_SIZE, STICK_VIEW_SIZE });
    direction_stick->set_center(_frame.size.center());
    add_subview(direction_stick);

    auto stick_center = direction_stick->frame().size.center();

    direction_stick->add_path(
            PointsPath::circle_with(stick_center, STICK_VIEW_SIZE),
            Color::black);

    direction_stick->add_path(
            PointsPath::circle_with(stick_center, STICK_VIEW_SIZE - OUTLINE_WIDTH),
            Color::light_gray);
    
    on_touch.subscribe([&](Touch* touch) {
        if (!touch->is_ended()) {
            on_touch_moved(touch->location);
        }
        else {
            direction_stick->set_center(_frame.size.center());
            on_direction_change({ });
        }
    });
}

#endif
