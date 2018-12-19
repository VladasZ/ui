//
//  Touch.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 8/21/18.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#include "Touch.hpp"

Touch::Touch(ID id, const ui::Point& location, Touch::Event event) : id(id), location(location), event(event) {

}

bool Touch::is_began() const {
	return event == Event::Began; 
}

bool Touch::is_moved() const {
	return event == Event::Moved; 
}

bool Touch::is_ended() const {
	return event == Event::Ended; 
}
