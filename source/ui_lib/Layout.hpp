//
//  Layout.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 1/11/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include "Rect.hpp"

namespace ui {

class View;

enum class Alignment {
    Left,
    Center,
    Right
};

class Layout {

    friend View;

    float _value;
    Edge _edge;
    View* _anchor = nullptr;

public:

    Layout(Edge edge, float value, View* anchor = nullptr);

private:

    void _layout_view(View*) const;
};

};
