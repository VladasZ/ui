//
//  MacOSConsoleDrawer.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/5/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#if defined(MAC_OS) || defined(LINUX)

#include "Drawer.hpp"

namespace ui {
	class MacOSConsoleDrawer : public Drawer {
		void _draw_rect(const Rect& rect) override;
		void _fill_rect(const Rect& rect, const Color& color) override;
	};
}

#endif
