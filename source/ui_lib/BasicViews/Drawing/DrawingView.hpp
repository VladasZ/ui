//
//  DrawingView.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 4/28/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include "Path.hpp"
#include "View.hpp"

namespace ui {

class PathData;

class DrawingView : public View {

    std::vector<PathData*> _paths;

public:

    using View::View;

    ~DrawingView() override;

    void add_path(gm::Path*);

protected:

    void _draw() override;

};

}
