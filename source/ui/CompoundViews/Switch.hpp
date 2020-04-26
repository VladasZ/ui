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

    protected:

        bool _is_selected = false;

        View* _switch;

    public:

        using View::View;

        bool is_selected() const;

        cu::Event<bool> on_value_changed;

    protected:

        void setup() override;
        void layout_subviews() override;

    };

}
