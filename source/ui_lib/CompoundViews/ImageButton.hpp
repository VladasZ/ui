//
//  ImageButton.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 1/28/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include "ImageView.hpp"

namespace ui {

class ImageButton : public ImageView {

public:

    std::function<void()> on_touch;

    ImageButton(const Rect& frame = { }, Image* image = nullptr);

    void touch_event(Touch*) override;
};

}
