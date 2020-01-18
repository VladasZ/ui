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
#include "Event.hpp"
#include "Label.hpp"

namespace ui {

class Button : public View {

    Label* _caption_label;

public:

    Event<> on_press;

    Button(const gm::Rect& = { });

    void set_caption(const std::string&);

protected:

};

}
