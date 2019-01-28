//
//  Label.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/29/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include "View.hpp"
#include "Font.hpp"

namespace ui {

class Label : public View {

    Alignment _aligment = Alignment::Left;
    std::string _text;
    View* _content_view;
    Font* _font;

public:

    Label(const Rect& = { });

public:

    std::string text() const;
    void set_text(const std::string&);
    void set_aligment(Alignment);

    void resize_to_fit_text();

private:

    void _set_glyphs();
};

}
