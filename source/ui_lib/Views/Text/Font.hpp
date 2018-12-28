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
    
    Font(const std::string& file_name);
    ~Font();
    
    float  baseline_shift()            const { return _baseline_shift; }
    float  height()                    const { return _height;         }
    ui::Glyph* glyph_for_char(char ch) const { return _glyphs[ch];     }
    
    Font* withSize(int size);
};

}
