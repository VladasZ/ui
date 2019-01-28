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

class Button;
class ImageView;

class SliderView : public View {

    float _value;

public:

    SliderView(const Rect& = { });

    float value() const;
    void set_value(float);

};

}
