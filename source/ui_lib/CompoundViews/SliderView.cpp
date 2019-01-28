//
//  SliderView.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 1/28/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#include "ImageButton.hpp"
#include "SliderView.hpp"

using namespace ui;

SliderView::SliderView(const Rect& frame) : View(frame) {

}

SliderView::~SliderView() {
    delete _increase_button;
    delete _decrease_button;
    delete _slider_content_view;
    delete _slider_view;
}

float SliderView::value() const {
    return  _value;
}

void SliderView::set_value(float value) {
    _value = value;
    if (_value < 0) _value = 0;
    if (_value > 1) _value = 1;
    _needs_layout = true;
    if (value_changed)
        value_changed(_value);
}

void SliderView::set_buttons_color(const Color& color) {
    _increase_button->color = color;
    _decrease_button->color = color;
}

void SliderView::set_slider_color(const Color& color) {
    _slider_view->color = color;
}

//ImageButton* _increase_button;
//ImageButton* _decrease_button;
//View* _slider_content_view;
//View* _slider_view;

void SliderView::_setup() {
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

    _increase_button->on_touch = [&] {
        this->set_value(this->value() + 0.05f);
    };

    _decrease_button->on_touch = [&] {
        this->set_value(this->value() - 0.05f);
    };
}

void SliderView::_layout() {
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

    _layout_constraints();
}

void SliderView::_set_slider_position() {
    _slider_view->set_frame({
                                0,
                                (_slider_content_view->frame().size.height - _frame.size.width / 4) * (1 - _value),
                                _frame.size.width,
                                _frame.size.width / 4
                            });
}
