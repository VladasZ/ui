//
//  LabeledGraphView.сpp
//  ui
//
//  Created by Vladas Zakrevskis on 29/01/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#include "LabeledGraphView.hpp"

using namespace ui;


void LabeledGraphView::set_caption(const std::string& caption) {
    _caption_label->set_text(caption);
}

void LabeledGraphView::_setup() {
    GraphView::_setup();
    add_subview(_caption_label = new Label());
}