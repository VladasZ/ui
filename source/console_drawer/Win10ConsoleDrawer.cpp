//
//  Win10ConsoleDrawer.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/5/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#ifdef WINDOWS

#include <iostream>
#include <Windows.h>
#include "Win10ConsoleDrawer.hpp"

using namespace std;
using namespace ui;

static void set_cursor_position(const Point& position) {
	COORD coord;
	coord.X = static_cast<SHORT>(position.x);
	coord.Y = static_cast<SHORT>(position.y);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Win10ConsoleDrawer::_draw_rect(const Rect& rect) {

	set_cursor_position({ rect.origin.x + 1, rect.origin.y });

	for (int i = 0; i < rect.size.width - 1; i++)
		cout << "_";

	for (int i = 0; i < rect.size.height; i++) {
		set_cursor_position({ rect.origin.x, rect.origin.y + static_cast<float>(i) + 1});
		cout << "|";
		set_cursor_position({ rect.origin.x + rect.size.width, rect.origin.y + static_cast<float>(i) + 1 });
		cout << "|";
	}

	set_cursor_position({ rect.origin.x + 1, rect.origin.y - 1 + rect.size.height + 1 });

	for (int i = 0; i < rect.size.width - 1; i++)
		cout << "_";
}

void Win10ConsoleDrawer::_fill_rect(const Rect& rect, const Color& color) {
	cout << "Win10ConsoleDrawer::fill_rect" << endl;
}

const Rect Win10ConsoleDrawer::_convert_rect(const Rect& rect) {
	return { rect.origin.x, rect.origin.y, rect.size.width * 2, rect.size.height };
}

#endif
