//
//  Label.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/29/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#include "ui.hpp"
#include "Label.hpp"
#include "Glyph.hpp"
#include "ImageView.hpp"

using namespace ui;
using namespace gm;

Label::Label(const Rect& frame) : View(frame) {
    _font = config::default_font;
    _content_view = new View(_frame.with_zero_origin());
    draw_debug_frame = false;
    _content_view->draw_debug_frame = false;
    add_subview(_content_view);
}

std::string Label::text() const {
    return _text;
}

void Label::set_text(const std::string& text) {
    _text = text;
    _needs_layout = true;
#ifdef USING_FREETYPE
    _set_glyphs();
#endif
}

void Label::set_font(Font* font) {
    _font = font;
    _needs_layout = true;
    _set_glyphs();
}

void Label::resize_to_fit_text() {
    _frame.size = static_cast<decltype(this)>(_content_view)->_frame.size;
    _needs_layout = true;
}

void Label::_set_glyphs() {

    _content_view->remove_all_subviews();

    if (_text.empty()) {
        return;
    }

    int advance = 0;
    float content_width = 0;
    auto& content_size = static_cast<decltype(this)>(_content_view)->_frame.size;

    content_size.height = _font->height();

    for (auto letter : _text) {
        auto glyph = _font->glyph_for_char(letter);

        auto glyph_view = new ImageView(glyph->size(), glyph->image);
        glyph_view->tint_color = text_color;
        glyph_view->draw_debug_frame = false;

        auto& glyph_view_frame = reinterpret_cast<decltype(this)>(glyph_view)->_frame;

        glyph_view_frame.origin = {
            advance + glyph->bearing.x,
            content_size.height / 2 - glyph->bearing.y + _font->baseline_shift()
        };

        _content_view->add_subview(glyph_view);
        advance += glyph->advance;
        content_width = glyph_view_frame.max_x();
    }

    content_size.width = content_width;

    static_cast<decltype(this)>(_content_view)->_needs_layout = true;
}
