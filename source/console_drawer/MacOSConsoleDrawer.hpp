//
//  MacOSConsoleDrawer.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/5/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#ifdef MAC_OS

#include "Drawer.hpp"

namespace ui {
	class MacOSConsoleDrawer : Drawer {
	public:
		void draw_rect(const Rect& rect) override;
		void fill_rect(const Rect& rect, const Color& color) override;
	};
}

#endif
