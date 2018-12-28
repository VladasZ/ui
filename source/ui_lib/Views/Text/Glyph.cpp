//
//  Glyph.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 1/18/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#include "Glyph.hpp"
#include "Image.hpp"

using namespace ui;


Glyph::Glyph(char ch, Image* image, int advance, const Point& bearing)
: ch(ch), image(image), advance(advance), bearing(bearing)
{ }

Glyph::~Glyph() {
    delete image;
}

Size Glyph::size() const {
    return image->size();
}

float Glyph::y_max() const {
    return bearing.y;
}

float Glyph::y_min() const {
    return bearing.y - image->size().height;
}
