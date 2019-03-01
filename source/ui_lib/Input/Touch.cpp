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

#if DESKTOP_BUILD

Touch::Touch(ID id, const Point& location, Event event, Mouse::Button button)
    : id(id), location(location), event(event), button(button) { }
#else
Touch::Touch(ID id, const Point& location, Touch::Event event)
    : id(id), location(location), event(event) { }
#endif

bool Touch::is_began() const {
    return event == Event::Began;
}

bool Touch::is_moved() const {
    return event == Event::Moved;
}

bool Touch::is_ended() const {
    return event == Event::Ended;
}

const char* Touch::event_string() const {
    static std::string result;

    if (is_began())
        result = "Began";

    if (is_moved())
        result = "Moved";

    if (is_ended())
        result = "Ended";

    return result.c_str();
}

const char* Touch::to_string() const {
    static std::string result;
    result = std::string() + location.to_string() + " " + event_string();
    return result.c_str();
}
