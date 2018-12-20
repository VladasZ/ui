//
//  Touch.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 8/21/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#include <string>

#include "Touch.hpp"

using namespace ui;

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

const char* Touch::to_string() const {
    static std::string result;
    std::string event = "Began";

    if (is_moved())
        event = "Moved";

    if (is_ended())
        event = "Ended";

    result = std::string() + location.to_string() + " " + event;
    return result.c_str();
}
