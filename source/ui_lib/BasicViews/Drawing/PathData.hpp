//
//  PathData.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 4/29/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include "Path.hpp"
#include "Color.hpp"

namespace ui {

class PathData {

    gm::Path* _path;
    gm::Color _color;
    void* _data;

public:

    PathData(gm::Path*, void*, const gm::Color& = gm::Color::green);

    const gm::Path* path() const;

    const gm::Color& color() const { return _color; }

    void* data() const;

};

}
