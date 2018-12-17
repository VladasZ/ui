//
//  Image.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/11/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#include "SOIL.h"

#include "Image.hpp"

using namespace ui;
using namespace std;

Image::Image(const string& path) {

	int width;
	int height;

	_data = SOIL_load_image(path.c_str(),
							&width,
							&height,
							&_channels,
							SOIL_LOAD_RGBA);

	if (_data == nullptr) 
		throw string() + "Failed to load image: " + path;

	_size = { static_cast<float>(width), static_cast<float>(height) };
}

Image::Image(const Size& size, void* data, int channels) : _data(data), _size(size), _channels(channels) {

}

Image::~Image() {
	_free_data();
}

const Size& Image::size() const {
	return _size;
}

bool Image::is_monochrome() const { 
	return _channels == 1; 
}

void Image::_free_data() {
	if (_data)
		free(_data);
}
