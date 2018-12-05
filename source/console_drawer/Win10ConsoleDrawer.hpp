//
//  Win10ConsoleDrawer.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/5/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#ifdef WINDOWS

#include "Drawer.hpp"

namespace ui {
  class Win10ConsoleDrawer : public Drawer {
  public:
	void draw_rect(const Rect& rect) override;
	void fill_rect(const Rect& rect, const Color& color) override;
  };
}

#endif
