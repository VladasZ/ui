//
//  ImageView.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/11/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#include "Image.hpp"
#include "ImageView.hpp"

using namespace ui;

ImageView::ImageView(const Rect& rect, Image* image) : View(rect), _image(image) {

}

const Image* ImageView::image() const {
	return _image;
}

void ImageView::set_image(Image* image) {
	_image = image;
}

void ImageView::draw() {
	_image->draw_in_rect(_absolute_frame);
}
