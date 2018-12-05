//
//  ui.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/5/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include "Drawer.hpp"

namespace ui::config {
	void set_drawer(Drawer* drawer);
	Drawer* drawer();
}
