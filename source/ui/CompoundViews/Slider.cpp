//
//  Slider.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 1/28/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#include "GmMath.hpp"
#include "Slider.hpp"
#include "ImageButton.hpp"

using namespace ui;
using namespace gm;

Slider::Slider(const Rect& frame) : View(frame) {

}

Slider::~Slider() {
    delete _increase_button;
    delete _decrease_button;
    delete _slider_content_view;
    delete _slider_view;
}

float Slider::value() const {
    return  _value * multiplier;
}

void Slider::set_value(float value) {
    _value = value / multiplier;
    gm::math::clamp(_value);
    _needs_layout = true;
    on_value_changed(value);
}

void Slider::set_buttons_color(const Color& color) {
    _increase_button->background_color = color;
    _decrease_button->background_color = color;
}

void Slider::set_slider_color(const Color& color) {
    _slider_view->background_color = color;
}

void Slider::_setup() {
    _increase_button     = new ImageButton();
    _decrease_button     = new ImageButton();
    _slider_content_view = new View();
    _slider_view         = new View();

    set_buttons_color(Color::blue);
    set_slider_color(Color::green);

    add_subview(_increase_button);
    add_subview(_decrease_button);
    add_subview(_slider_content_view);
    _slider_content_view->add_subview(_slider_view);

    _increase_button->on_press.subscribe([&] {
        set_value((this->_value + 0.005f) * multiplier);
    });

    _decrease_button->on_press.subscribe([&] {
        set_value((this->_value - 0.005f) * multiplier);
    });
    
    _slider_content_view->enable_user_interaction();
    _slider_content_view->on_touch.subscribe([&](Touch* touch){
        if (touch->is_ended()) {
            return;
        }
        set_value((1.0f - touch->location.y / _slider_content_view->frame().size.height) * multiplier);
    });
}

void Slider::_layout() {
    _calculate_absolute_frame();

    _increase_button->set_frame({ _frame.size.width });

    _decrease_button->set_frame({
                                    0,
                                    _frame.size.height - _frame.size.width,
                                    _frame.size.width,
                                    _frame.size.width
                                });

    _slider_content_view->set_frame({
                                        0,
                                        _frame.size.width,
                                        _frame.size.width,
                                        _frame.size.height - _frame.size.width * 2
                                    });

    _set_slider_position();
}

void Slider::_set_slider_position() {
    _slider_view->set_frame({
                                0,
                                (_slider_content_view->frame().size.height - _frame.size.width / 4) * (1 - _value),
                                _frame.size.width,
                                _frame.size.width / 4
                            });
}
