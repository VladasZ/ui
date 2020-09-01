//
//  main.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/5/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#include "Log.hpp"
#include "View.hpp"

int main() {

    auto view = new ui::View({ 10, 10, 10, 10 });
    Log << view->frame();
 
	return 0;
}
