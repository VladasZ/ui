//
//  UIImage.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/11/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#include "SOIL.h"

#include "ui.hpp"
#include "UIImage.hpp"

using namespace ui;

UIImage::Drawer::~Drawer() { }

UIImage::UIImage(const std::string& path) : Image(path) {
    _drawer = config::drawer()->init_image_drawer(this);
}

UIImage::UIImage(void* data, const Size& size, uint8_t channels) : Image(data, size.width, size.height, channels) {
    _drawer = config::drawer()->init_image_drawer(this);
}

const Size& UIImage::size() const {
    return reinterpret_cast<const Size&>(_width);
}

void UIImage::draw_in_rect(const Rect& rect) {
    _drawer->draw_in_rect(rect);
}
