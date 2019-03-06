//
//  main.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/5/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#include <iostream>
using namespace std;

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

static FT_Library ftLibrary() {
  static FT_Library _library = nullptr;
  if (_library == nullptr)
    FT_Init_FreeType(&_library);
  return _library;
}

#include "View.hpp"

#include "Rect.hpp"

using namespace gm;

int main() {

    Rect test = { 1, 2, 3, 4 };

    cout << test.to_string() << endl;

    cout << ftLibrary() << endl;

	return 0;
}
