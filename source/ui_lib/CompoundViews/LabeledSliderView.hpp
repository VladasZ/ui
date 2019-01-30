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


public:

    using View::View;

    SliderView* slider_view = nullptr;

    void set_caption(const std::string&);

private:

    void _setup() override;
    void _layout() override;

};

}
