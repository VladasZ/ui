//
//  StackView.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/29/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include "View.hpp"

namespace ui {

class StackView : public View {

    Alignment _alignment = Alignment::Center;

public:

    using View::View;

    void set_aligment(Alignment);

protected:

    void _layout() override;
};

}
