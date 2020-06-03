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


Label::Label(const Rect& frame) : View(frame) {
    _font = config::default_font;
    init_view(_content_view);
}

const std::string& Label::text() const {
    return _text;
}

void Label::set_text(const std::string& text) {
    _text = text;
#ifdef USING_FREETYPE
    _set_glyphs();
#endif
}

void Label::set_font(Font* font) {
    _font = font;
    _set_glyphs();
}

void Label::_set_glyphs() {

    _content_view->remove_all_subviews();

    if (_text.empty()) return;

    Float advance = 0;
    auto& content_size = _content_view->edit_frame().size;

    content_size.height = _font->height();

    for (auto letter : _text) {
        auto glyph = _font->glyph_for_char(letter);

        auto glyph_view = new ImageView(glyph->size(), glyph->image);
        glyph_view->tint_color = text_color;
        glyph_view->draw_debug_frame = false;

        glyph_view->edit_frame().origin = {
            advance + glyph->bearing.x,
            content_size.height - glyph->bearing.y + _font->baseline_shift()
        };

        _content_view->add_subview(glyph_view);
        advance += glyph->advance;
    }

    content_size.width = _content_view->subviews().back()->frame().max_x();

}

void Label::backspace() {
    if (_text.empty()) return;
    _text.pop_back();
    _content_view->remove_last_subview();
    if (_text.empty()) {
        _content_view->edit_frame().size.width = 0;
    }
    else {
        _content_view->edit_frame().size.width = _content_view->subviews().back()->frame().max_x();
    }
}

void Label::layout_subviews() {
    _content_view->place_at_center_vertically();
}
