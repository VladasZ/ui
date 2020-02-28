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

    protected:

        Label* _caption_label;

    public:

        cu::Event<> on_press;

        ~Button();
        Button(const gm::Rect& = { });

        void set_caption(const std::string&);

    };

}
