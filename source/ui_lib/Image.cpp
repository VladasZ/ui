//
//  Image.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/11/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#include "SOIL.h"

#include "ui.hpp"
#include "Image.hpp"

using namespace ui;
using namespace std;

Image::Drawer::~Drawer() { }

Image::Image(const string& path) {

	int width;
	int height;
    int channels;

	_data = SOIL_load_image(path.c_str(),
							&width,
							&height,
                            &channels,
							SOIL_LOAD_RGBA);

	if (_data == nullptr) 
		throw string() + "Failed to load image: " + path;

    _size     = { static_cast<float>(width), static_cast<float>(height) };
    _channels = static_cast<uint8_t>(channels);

    _drawer = config::drawer()->init_image_drawer(this);
}

Image::Image(const Size& size, void* data, uint8_t channels) : _data(data), _size(size), _channels(channels) {
    _drawer = config::drawer()->init_image_drawer(this);
}

Image::~Image() {
	_free_data();
}

const Size& Image::size() const {
	return _size;
}

void* Image::data() const {
    return _data;
}

uint8_t Image::channels() const {
    return _channels;
}

bool Image::is_monochrome() const { 
	return _channels == 1; 
}

void Image::draw_in_rect(const Rect& rect) {
    _drawer->draw_in_rect(rect);
}

void Image::_free_data() {    
    if (_data) {
		free(_data);
        _data = nullptr;
    }
}
