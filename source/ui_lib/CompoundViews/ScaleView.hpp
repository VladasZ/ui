//
//  ScaleView.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 4/4/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include "DrawingView.hpp"

namespace ui {

class ScaleView : public View {


    PathData* _path = nullptr;
    DrawingView* _drawing_view = nullptr;

    size_t _count = 0;

public:

    ScaleView(size_t count);

    size_t count() const;

private:

    void _layout() override;
    void _draw() override;
    void _create_lines();

};

}
