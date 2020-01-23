//
//  Slider.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 1/28/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include "View.hpp"
#include "Slider.hpp"
#include "ImageButton.hpp"

namespace ui {

class Slider : public View {

protected:

    float _value = 0.0f;

    ImageButton* _increase_button;
    ImageButton* _decrease_button;
    View* _slider_content_view;
    View* _slider_view;

public:

    float multiplier = 1.0f;

    Event<float> on_value_changed;

    Slider(const gm::Rect& = { });
    ~Slider() override;

    float value() const;
    void set_value(float);

    void set_buttons_color(const gm::Color&);
    void set_slider_color(const gm::Color&);

protected:

    void _setup() override;

    void _layout() override;

    void _set_slider_position();
};

}
