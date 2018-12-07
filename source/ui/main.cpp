//
//  main.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/5/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#include <iostream>
using namespace std;

#include "View.hpp"

#include "ui.hpp"
#include "ConsoleDrawer.hpp"

int main() {

#if !LINUX
  
	ui::config::set_drawer(new ui::ConsoleDrawer());

	auto view1 = new ui::View({ 10, 10, 15, 15 });
	auto view2 = new ui::View({ 3, 3, 10, 10 });
	auto view3 = new ui::View({ 1, 1, 5, 5 });

	view1->add_subview(view2);
	view2->add_subview(view3);

	view1->draw();
#endif

	return 0;
}
