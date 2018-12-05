//
//  Drawer.hpp
//  TestEngine
//
//  Created by Vladas Zakrevskis on 12/5/19.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include "Rect.hpp"
#include "Color.hpp"

namespace ui {

	class Drawer {
	public:

		virtual void draw_rect(const Rect& rect) = 0;
		virtual void fill_rect(const Rect& rect, const Color& color) = 0;

	};


}