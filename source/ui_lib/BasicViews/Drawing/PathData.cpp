//
//  PathData.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 4/29/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#include "PathData.hpp"

using namespace ui;
using namespace gm;

PathData::PathData(Path* path, void* data) : _path(path), _data(data) {

}

const Path* PathData::path() const {
    return _path;
}

void* PathData::data() const {
    return _data;
}
