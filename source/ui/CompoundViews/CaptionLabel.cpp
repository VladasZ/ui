//
//  CaptionLabel.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 11/02/2020.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#include "CaptionLabel.hpp"

using namespace ui;
using namespace gm;

void CaptionLabel::set_caption(const std::string& caption) {
    _caption_label->set_text(caption);
}

void CaptionLabel::set_text(const std::string& text) {
    _text_label->set_text(text);
}

void CaptionLabel::_setup() {
    add_subview(_caption_label = new Label());
    add_subview(_text_label = new Label());
}

void CaptionLabel::_layout() {
    _calculate_absolute_frame();

    const auto width = _frame.size.width / 3;
    const auto height = _frame.size.height;

    _caption_label->edit_frame() =
            { 0,
              0,
              width,
              height
            };

    _text_label->edit_frame() =
            { width,
              0,
              width * 2,
              height
            };

    _layout_subviews();
}
