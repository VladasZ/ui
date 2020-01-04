//
//  LabeledSliderView.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 1/29/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#include "ui.hpp"
#include "Font.hpp"
#include "Button.hpp"
#include "LabeledSliderView.hpp"

using namespace ui;

void LabeledSliderView::set_caption(const std::string& caption) {
    _caption_label->set_text(caption);
}

void LabeledSliderView::set_slider_color(const gm::Color& color) {
    slider_view->set_slider_color(color);
}

void LabeledSliderView::_setup() {
    _caption_label = new Label();
    _value_label   = new Label();
    _reset_button  = new Button();
    slider_view    = new SliderView();

    _value_label->set_text("0.00");

    slider_view->on_value_changed.subscribe([&](float value) {
        _value_label->set_text(std::to_string(value).substr(0, 4));
    });

    _reset_button->on_press.subscribe([&]{
        slider_view->set_value(0.5f);
    });

    add_subview(_caption_label);
    add_subview(_value_label);
    add_subview(_reset_button);
    add_subview(slider_view);
}

void LabeledSliderView::_layout() {
    _calculate_absolute_frame();

    static const float label_height = 28.0f;
    static const float slider_width = 28.0f;

    _value_label->set_frame({
                                0,
                                0,
                                _frame.size.width,
                                label_height,
                            });

    slider_view->set_frame({
                                _frame.size.width / 2 - slider_width / 2,
                                label_height,
                                slider_width,
                                _frame.size.height - label_height * 2
                            });

    _caption_label->set_frame({
                                  0,
                                  _frame.size.height - label_height,
                                  _frame.size.width,
                                  label_height
                              });

    _reset_button->set_frame(_caption_label->frame());

}