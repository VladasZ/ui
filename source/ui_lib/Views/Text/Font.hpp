//
//  Font.hpp
//  TestEngine
//
//  Created by Vladas Zakrevskis on 9/26/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

#include <string>
#include <vector>

namespace ui {

class Glyph;

class Font {
    
    float _height;
    float _baseline_shift;

    std::vector<Glyph*> _glyphs;
  
public:
    
    Font(const std::string& file_name, unsigned int size = 28);
    ~Font();
    
    float  baseline_shift()            const;
    float  height()                    const;
    ui::Glyph* glyph_for_char(char ch) const;
};

}