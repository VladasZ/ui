//
//  Win10ConsoleDrawer.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/5/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#ifdef WINDOWS

#include <iostream>

#include "Win10ConsoleDrawer.hpp"

using namespace std;
using namespace ui;

void Win10ConsoleDrawer::draw_rect(const Rect& rect) {
	cout << "Win10ConsoleDrawer::draw_rect" << endl;
}

void Win10ConsoleDrawer::fill_rect(const Rect& rect, const Color& color) {
	cout << "Win10ConsoleDrawer::fill_rect" << endl;
}

#endif
