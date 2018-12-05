//
//  main.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/5/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#include <Windows.h>

#include <iostream>
using namespace std;

#include "View.hpp"

#include "ConsoleDrawer.hpp"

int main() {

	ui::ConsoleDrawer drawer;

	drawer.draw_rect({ 0, 0, 5, 5 });


	drawer.draw_rect({ 10, 10, 10, 10 });
	drawer.draw_rect({ 10, 10, 3, 3 });


	drawer.draw_rect({ 30, 10, 10, 10 });


	//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//// you can loop k higher to see more color choices
	//for (int k = 1; k < 255; k++)
	//{
	//	// pick the colorattribute k you want
	//	SetConsoleTextAttribute(hConsole, k);
	//	cout << k << " I want to be nice today!";
	//}

	return 0;
}
