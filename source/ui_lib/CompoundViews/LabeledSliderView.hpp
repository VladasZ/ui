//
//  LabeledSliderView.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 1/29/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include "Label.hpp"
#include "SliderView.hpp"

namespace ui {

class LabeledSliderView : public View {


    Label*      _caption_label = nullptr;
    Label*      _value_label   = nullptr;
    SliderView* _slider_view   = nullptr;


public:

    using View::View;

    Event<float> on_value_changed;

    float value() const;
    void set_value(float);

    void set_caption(const std::string&);

private:

    void _setup() override;
    void _layout() override;

};

}
