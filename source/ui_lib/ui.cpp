//
//  ui.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/5/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#include <string>

#include "ui.hpp"

using namespace ui;
using namespace std;

static Drawer* _drawer;

void config::set_drawer(Drawer* drawer) {
	if (_drawer)
		delete _drawer;
	_drawer = drawer;
}

Drawer* config::drawer() {
	if (_drawer == nullptr)
		throw string() + "Accessign nullptr ui::Drawer";
	return _drawer;
}