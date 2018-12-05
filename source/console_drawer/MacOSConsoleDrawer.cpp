//
//  MacOSConsoleDrawer.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/5/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#ifdef MAC_OS

#include <iostream>

#include "MacOSConsoleDrawer.hpp"

using namespace std;
using namespace ui;

void MacOSConsoleDrawer::draw_rect(const Rect& rect) {
	cout << "MacOSConsoleDrawer::draw_rect" << endl;
}

void MacOSConsoleDrawer::fill_rect(const Rect& rect, const Color& color) {
	cout << "MacOSConsoleDrawer::fill_rect" << endl;
}

#endif
