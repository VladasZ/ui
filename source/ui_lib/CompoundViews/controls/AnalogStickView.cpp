//
//  AnalogStickView.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 3/12/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

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

    const float max_lenght = _frame.size.height / 2;

    Point touch_position = global_point_lo_local(touch);
    Point vector = touch_position - _frame.size.center();

    if (vector.length() > max_lenght) {
        vector.set_length(max_lenght);
        touch_position = _frame.size.center() + vector;
    }

    direction_stick->set_center(touch_position);
    on_direction_change(vector * 0.1f);
}

void AnalogStickView::_setup() {
    add_path(
            Path::circle_with(_frame.size.center(), _frame.size.width),
            Color::black);

    add_path(
            Path::circle_with(_frame.size.center(), _frame.size.width - OUTLINE_WIDTH),
            Color::white);

    direction_stick = new DrawingView({ STICK_VIEW_SIZE, STICK_VIEW_SIZE });
    direction_stick->set_center(_frame.size.center());
    add_subview(direction_stick);

    direction_stick->background_color = Color::green;
    
    direction_stick->add_path(
            Path::circle_with(_frame.size.center(), STICK_VIEW_SIZE),
            Color::black);

    direction_stick->add_path(
            Path::circle_with(_frame.size.center(), STICK_VIEW_SIZE - OUTLINE_WIDTH),
            Color::light_gray);

    Input::on_touch.subscribe([&](Touch* touch) {
        if (touch->is_moved()) {
            on_touch_moved(touch->location);
            return;
        }
        if (touch->is_ended()) {
            direction_stick->set_center(_frame.size.center());
            on_direction_change({ });
        }
    });
}
