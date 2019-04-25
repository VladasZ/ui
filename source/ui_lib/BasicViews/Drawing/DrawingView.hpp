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

public:

    using Paths = std::vector<PathData*>;

private:

    Paths _paths;

public:

    using View::View;

    ~DrawingView() override;

    const Paths& paths() const;
    void add_path(gm::Path*, const gm::Color&);

    void remove_all_paths();

protected:

    void _draw() override;

};

}
