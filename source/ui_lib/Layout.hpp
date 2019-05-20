
//
//  Layout.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 1/11/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include <cstdint>

#include "Rect.hpp"

namespace ui {

class View;

enum class Alignment {
    Left,
    Center,
    Right
};

enum class Anchor {
    None        = 0b00000000,
    Width       = 0b00000001,
    Height      = 0b00000010,
    Top         = 0b00000100,
    Bottom      = 0b00001000,
    Right       = 0b00010000,
    Left        = 0b00100000,
    CenterH     = 0b01000000,
    CenterV     = 0b10000000,
    Size        = Width   | Height,
    TR          = Top     | Right,
    TL          = Top     | Left,
    BR          = Bottom  | Right,
    BL          = Bottom  | Left,
    Center      = CenterH | CenterV,
    Background  = Top     | Bottom  | Right   | Left,
    _Horisontal = Width   | Right   | Left    | CenterH,
    _Vertical   = Height  | Top     | Bottom  | CenterV
};

class Layout {

    friend View;

    float _value;
    Anchor _anchor;
    View* _anchor_view = nullptr;

public:

    Layout(Anchor anchor, float value = 0, View* anchor_view = nullptr);

public:

    bool has_width() const;
    bool has_height() const;

private:

    void _layout_view(View*) const;

private:

    enum OneDimensionAnchor : uint64_t {
        None   = static_cast<uint64_t>(Anchor::None),
        Size   = static_cast<uint64_t>(Anchor::Width)   | static_cast<uint64_t>(Anchor::Height),
        Origin = static_cast<uint64_t>(Anchor::Left)    | static_cast<uint64_t>(Anchor::Top),
        Length = static_cast<uint64_t>(Anchor::Right)   | static_cast<uint64_t>(Anchor::Bottom),
        Center = static_cast<uint64_t>(Anchor::CenterH) | static_cast<uint64_t>(Anchor::CenterV)
    };

private:

    void _layout_one_dimension(float& origin, float& size, const float& space_size, bool const_size, OneDimensionAnchor anchor) const;

    void _layout_length(              const float& origin,       float& size, const float& space_size) const;
    void _layout_origin(                    float& origin,       float& size)                          const;
    void _layout_center(                    float& origin, const float& size, const float& space_size) const;
    void _layout_length_preserve_size(      float& origin, const float& size, const float& space_size) const;
    void _layout_origin_preserve_size(      float& origin)                                             const;

};

};
