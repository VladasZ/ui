//
//  SliderView.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 1/28/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#include "SliderView.hpp"

using namespace ui;

SliderView::SliderView(const Rect& frame) : View(frame) {

}

float SliderView::value() const {
    return  _value;
}

void SliderView::set_value(float value) {
    _value = value;
    _needs_layout = true;
}
