//
//  ConsoleDrawer.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/5/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include "Win10ConsoleDrawer.hpp"
#include "MacOSConsoleDrawer.hpp"

namespace ui {
#if WINDOWS
	using ConsoleDrawer = Win10ConsoleDrawer;
#else
	using ConsoleDrawer = MacOSConsoleDrawer;
#endif
}
