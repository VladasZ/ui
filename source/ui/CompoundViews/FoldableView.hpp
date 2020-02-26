//
//  FoldableView.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 27/02/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#include "View.hpp"
#include "Button.hpp"

namespace ui {

class FoldableView : public View {

public:

    using View::View;

    View* main_view;
    View* hidden_view;

    void set_folded(bool);

protected:

    Button* _unfold_button;

    bool _folded = true;

    void _setup() override;
    void _layout() override;

};


}
