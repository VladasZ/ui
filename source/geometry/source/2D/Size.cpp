//
//  Size.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 8/20/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#include "Size.hpp"

using namespace ui;

Size::Size(float width, float height) : width(width), height(height) { 

}

Point Size::center() const {
	return { width / 2, height / 2 };
}

float Size::ratio() const {
	return width / height;
}

Size Size::operator / (float value) const {
	return { this->width / value, this->height / value };
}

Size Size::operator * (float value) const {
	return { this->width * value, this->height * value };
}

bool Size::operator == (const Size& size) const {
	return this->width == size.width && this->height == size.height;
}
