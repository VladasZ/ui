//
//  SliderView.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 1/28/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include "View.hpp"

namespace ui {

class ImageButton;

class SliderView : public View {

    float _value = 0.0f;

    ImageButton* _increase_button;
    ImageButton* _decrease_button;
    View* _slider_content_view;
    View* _slider_view;

public:

    float multiplier = 1.0f;

    Event<float> on_value_changed;

    SliderView(const gm::Rect& = { });
    ~SliderView() override;

    float value() const;
    void set_value(float);

    void set_buttons_color(const gm::Color&);
    void  set_slider_color(const gm::Color&);

private:

    void _setup() override;

    void _layout() override;

    void _set_slider_position();
};

}
