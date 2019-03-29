//
//  PathData.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 4/29/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include "Path.hpp"

namespace ui {

class PathData {

    gm::Path* _path;
    void* _data;

public:

    PathData(gm::Path*, void*);

    const gm::Path* path() const;

    void* data() const;

};

}
