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

    enum class DrawMode {
        Outline,
        Fill
    };

public:

    DrawMode draw_mode;

    PathData(gm::Path*, void*, const gm::Color& = gm::Color::green, DrawMode drawMode = DrawMode::Outline);
    ~PathData();

    const gm::Path* path() const;

    const gm::Color& color() const { return _color; }

    void* data() const;

};

}
