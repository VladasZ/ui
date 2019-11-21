//
//  ImageButton.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 1/28/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include "Event.hpp"
#include "ImageView.hpp"

namespace ui {

class ImageButton : public ImageView {

public:

    Event<> on_press;

    ImageButton(const gm::Rect& frame = { }, Image* image = nullptr);
    
};

}
