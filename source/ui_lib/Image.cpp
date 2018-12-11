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

Image::~Image() {
	SOIL_free_image_data(static_cast<unsigned char*>(_data));
}

const void* Image::data() const {
	return _data;
}

Size Image::size() const {
	return _size;
}

int Image::channels() const {
	return _channels;
}