//
//  Font.cpp
//  TestEngine
//
//  Created by Vladas Zakrevskis on 9/26/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include <cmath>

#include "Font.hpp"
#include "Glyph.hpp"
#include "Image.hpp"

using namespace ui;
using namespace std;

static FT_Library ft_library() {
    static FT_Library _library = nullptr;
    if (_library == nullptr)
        FT_Init_FreeType(&_library);
    return _library;
}

static ui::Glyph* render_glyph(const FT_Face& face, char ch) {

      int glyphIndex = FT_Get_Char_Index(face, ch);

      FT_Load_Glyph(face,
                    glyphIndex,
                    FT_LOAD_RENDER);

      FT_BitmapGlyph bitmapGlyhp;
      FT_Get_Glyph(face->glyph, (FT_Glyph*)&bitmapGlyhp);

      auto image = new ui::Image(ui::Size((float)bitmapGlyhp->bitmap.width,
                                  (float)bitmapGlyhp->bitmap.rows),
                             bitmapGlyhp->bitmap.buffer,
                             1);

      return new Glyph(ch,
                       image,
                       (int)face->glyph->metrics.horiAdvance / 64,
                   ui::Point((float)face->glyph->metrics.horiBearingX / 64,
                             (float)face->glyph->metrics.horiBearingY / 64));



    
//      FT_UInt glyph_index = FT_Get_Char_Index(face, static_cast<FT_ULong>(ch));
    
//      FT_Load_Glyph(face,
//                    glyph_index,
//                    FT_LOAD_RENDER);

//      FT_BitmapGlyph bitmapGlyhp;
//      FT_Get_Glyph(face->glyph, (FT_Glyph*)(&bitmapGlyhp));
    
//      Size size = { static_cast<float>(bitmapGlyhp->bitmap.width), static_cast<float>(bitmapGlyhp->bitmap.rows) };

//      auto image = new Image(size,
//                             bitmapGlyhp->bitmap.buffer,
//                             1);

//      Point bearing = { static_cast<float>(face->glyph->metrics.horiBearingX / 64),
//                        static_cast<float>(face->glyph->metrics.horiBearingY / 64) };

//      return new Glyph(ch,
//                       image,
//                       static_cast<int>(face->glyph->metrics.horiAdvance / 64),
//                       bearing);
}

Font::Font(const std::string& file_name) {

    FILE* file = fopen(file_name.c_str(), "rb");
    if (file == nullptr)
        throw string() + "Failed to open file: " + file_name;

    fseek(file, 0, SEEK_END);
    auto file_size = static_cast<FT_Long>(ftell(file));
    fseek(file, 0, SEEK_SET);
    auto data = new unsigned char[static_cast<unsigned long>(file_size)];
    fread(data, 1, static_cast<size_t>(file_size), file);
    
    FT_Face face;
    
    FT_New_Memory_Face(ft_library(),
                       data,
                       file_size,
                       0,
                       &face);
    
    FT_Set_Pixel_Sizes(face,
                       0,
                       static_cast<FT_UInt>(file_size));
    
    float y_max = 0;
    float y_min = 0;

    for (int i = 0; i < 128; i++) {
        auto glyph = render_glyph(face, static_cast<char>(i));
        
        if (y_max < glyph->y_max()) y_max = glyph->y_max();
        if (y_min > glyph->y_min()) y_min = glyph->y_min();
        
        _glyphs.push_back(glyph);
    }
    
    _height = y_max - y_min;
    
    float baselinePosition = std::fabs(static_cast<float>(y_min));
    
    _baseline_shift = _height / 2 - baselinePosition;

    fclose(file);
}

Font::~Font() {
    for (auto glyph : _glyphs)
        delete glyph;
}

