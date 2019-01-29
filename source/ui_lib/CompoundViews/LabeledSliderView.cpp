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

float LabeledSliderView::value() const {
    if (_slider_view)
        return _slider_view->value();
    return -1.0f;
}

void LabeledSliderView::set_value(float value) {
    if (_slider_view)
        _slider_view->set_value(value);
}

void LabeledSliderView::set_caption(const std::string& caption) {
    _caption_label->set_text(caption);
}

void LabeledSliderView::_setup() {
    _caption_label = new Label();
    _value_label   = new Label();
    _slider_view   = new SliderView();

    _value_label->set_text("0.00");

    _slider_view->on_value_changed.subscribe([&](float value) {
        on_value_changed(value);
        _value_label->set_text(std::to_string(value).substr(0, 4));
    });

    add_subview(_caption_label);
    add_subview(_value_label);
    add_subview(_slider_view);
}

void LabeledSliderView::_layout() {
    _calculate_absolute_frame();
    _layout_constraints();

    static const float label_height = 28.0f;

    _value_label->set_frame({
                                0,
                                0,
                                _frame.size.width,
                                label_height,
                            });

    _slider_view->set_frame({
                                0,
                                label_height,
                                _frame.size.width,
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
