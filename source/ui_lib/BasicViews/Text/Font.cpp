//
//  Font.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 9/26/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#include "ui.hpp"

#ifndef NO_FREETYPE

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#endif

#include <cmath>

#include "Font.hpp"
#include "Glyph.hpp"
#include "Image.hpp"

using namespace ui;
using namespace gm;

#ifndef NO_FREETYPE
static FT_Library ft_library() {
    static FT_Library _library = nullptr;
    if (_library == nullptr)
        FT_Init_FreeType(&_library);
    return _library;
}

static Glyph* render_glyph(const FT_Face& face, char ch) {

    FT_UInt glyphIndex = FT_Get_Char_Index(face, static_cast<FT_ULong>(ch));

    FT_Load_Glyph(face, glyphIndex, FT_LOAD_RENDER);

	FT_Glyph ft_glyph;
    FT_Get_Glyph(face->glyph, &ft_glyph);

	auto bitmap_glyph = reinterpret_cast<FT_BitmapGlyph>(ft_glyph);

	Size size = { bitmap_glyph->bitmap.width, bitmap_glyph->bitmap.rows };

    Point bearing = { face->glyph->metrics.horiBearingX / 64,
                      face->glyph->metrics.horiBearingY / 64 };

	auto glyph = new Glyph(ch,
		                   new Image(bitmap_glyph->bitmap.buffer, size.width, size.height, 1),
						   static_cast<int>(face->glyph->metrics.horiAdvance / 64),
						   bearing);
	
	FT_Done_Glyph(ft_glyph);

    return glyph;
}
#endif


Font::Font(const std::string& file_name, unsigned int size) : _file(file_name) {
#ifndef NO_FREETYPE

    FILE* file = fopen(file_name.c_str(), "rb");

    if (file == nullptr)
        throw std::string() + "Failed to open font file: " + file_name;

    fseek(file, 0, SEEK_END);
    auto _size = static_cast<size_t>(ftell(file));
    fseek(file, 0, SEEK_SET);
    auto _data = new char[_size];
    fread(_data, 1, _size, file);
    fclose(file);
    
    FT_Face face;

    FT_New_Memory_Face(ft_library(),
                       reinterpret_cast<FT_Byte*>(_data),
                       static_cast<FT_Long>(_size),
                       0,
                       &face);

    FT_Set_Pixel_Sizes(face, 0, size);

    float y_max = 0;
    float y_min = 0;

    for (int i = 0; i < 128; i++) {
      auto glyph = render_glyph(face, static_cast<char>(i));

      if (y_max < glyph->y_max())
          y_max = glyph->y_max();

      if (y_min > glyph->y_min())
          y_min = glyph->y_min();

      _glyphs.push_back(glyph);
    }

    _height = y_max - y_min;

    float baseline_position = std::fabs(y_min);

    _baseline_shift = _height / 2 - baseline_position;
#endif
}

Font::~Font() {
    for (auto glyph : _glyphs)
        delete glyph;
}

float Font::baseline_shift() const {
    return _baseline_shift;
}

float Font::height() const {
    return _height;
}

Glyph* Font::glyph_for_char(char ch) const {
    return _glyphs[static_cast<size_t>(ch)];
}

Font* Font::with_size(unsigned int size) const {
    return new Font(_file, size);
}
