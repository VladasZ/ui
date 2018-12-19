//
//  Input.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/18/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include "stdint.h"

#include <vector>

#include "Point.hpp"
#include "Touch.hpp"

namespace ui {

class View;

class Input final {

    std::vector<View*> _subscribed_views;

public:


};

}
