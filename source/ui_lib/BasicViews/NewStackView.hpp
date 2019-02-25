//
//  NewStackView.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/29/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include "View.hpp"

namespace ui {

class NewStackView : public View {

public:

    using View::View;

protected:

    void _layout() override;

};

}
