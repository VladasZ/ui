//
//  Button.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 1/28/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include <functional>

#include "View.hpp"

namespace ui {

class Button : public View {

public:

    ~Button() override;

    std::function<void()> on_touch;

    Button(const Rect& = { });

    void touch_event(Touch*) override;
};

}
