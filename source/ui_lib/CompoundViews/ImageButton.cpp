//
//  ImageButton.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 1/28/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#include "ImageButton.hpp"

using namespace ui;

ImageButton::ImageButton(const Rect& frame, Image* image) : ImageView(frame, image) {
    enable_user_interaction();
}

void ImageButton::touch_event(Touch* touch) {
    View::touch_event(touch);
    if (on_touch && touch->is_began())
        on_touch();
}