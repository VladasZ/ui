//
//  Switch.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 17/12/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include "View.hpp"

namespace ui {

class Switch : public View {

    View* _switch;

public:

    using View::View;

    bool is_selected = false;

    Event<bool> on_value_changed;

protected:

    void _setup() override;
    void _layout() override;

};


}
