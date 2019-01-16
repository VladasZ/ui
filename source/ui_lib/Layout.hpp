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

enum class Anchor {
    Width      = 0b00000001,
    Height     = 0b00000010,
    Top        = 0b00000100,
    Bottom     = 0b00001000,
    Right      = 0b00010000,
    Left       = 0b00100000,
    CenterH    = 0b01000000,
    CenterV    = 0b10000000,
    TR         = Top     | Right,
    TL         = Top     | Left,
    BR         = Bottom  | Right,
    BL         = Bottom  | Left,
    Center     = CenterH | CenterV,
    Background = Top | Bottom | Right | Left
};

class Layout {

    friend View;

    float _value;
    Anchor _anchor;
    View* _anchor_view = nullptr;

public:

    Layout(Anchor anchor, float value = 0, View* anchor_view = nullptr);

private:

    void _layout_view(View*) const;

};

};
