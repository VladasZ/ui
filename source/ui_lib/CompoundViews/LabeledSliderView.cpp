//
//  LabeledSliderView.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 1/29/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#include "ui.hpp"
#include "Font.hpp"
#include "LabeledSliderView.hpp"

using namespace ui;

void LabeledSliderView::set_caption(const std::string& caption) {
    _caption_label->set_text(caption);
}

void LabeledSliderView::_setup() {
    _caption_label = new Label();
    _value_label   = new Label();
    slider_view   = new SliderView();

    _caption_label->set_aligment(Alignment::Center);
    _value_label  ->set_aligment(Alignment::Center);

    _value_label->set_text("0.00");

    slider_view->on_value_changed.subscribe([&](float value) {
        _value_label->set_text(std::to_string(value).substr(0, 4));
    });

    add_subview(_caption_label);
    add_subview(_value_label);
    add_subview(slider_view);
}

void LabeledSliderView::_layout() {
    _calculate_absolute_frame();
    _layout_constraints();

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


    //_layout_subviews();
}
