//
//  Glyph.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 1/18/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include "Rect.hpp"

class Image;

namespace ui {

class Glyph {

public:
    
    const char ch;
    Image* const image;
    const int advance;
    const Point bearing;
    
    Glyph(char ch, Image* image, int advance, const Point& bearing);
    ~Glyph();
    
    Size size() const;
    float y_max() const;
    float y_min() const;
};

}
