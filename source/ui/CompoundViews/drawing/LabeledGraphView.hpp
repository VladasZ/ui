//
//  LabeledGraphView.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 29/01/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#include "Label.hpp"
#include "GraphView.hpp"

namespace ui {

class LabeledGraphView : public GraphView {

    Label* _caption_label = nullptr;

public:

    using GraphView::GraphView;

    void set_caption(const std::string&);

protected:

    void _setup() override;

};

}
