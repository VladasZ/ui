//
//  ImageView.cpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/11/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#include "ui.hpp"

#include "ImageView.hpp"

using namespace ui;

ImageView::ImageView(UIImage* image) : ImageView({ }, image) {

}

ImageView::ImageView(const Rect& rect, UIImage* image) : View(rect), _image(image) {
    _content_view = new View();
    add_subview(_content_view);
}

const UIImage* ImageView::image() const {
    return _image;
}

void ImageView::set_image(UIImage* image) {
    _image = image;
}

void ImageView::set_content_mode(ContentMode mode) {
    _content_mode = mode;
}

void ImageView::_draw() {

    if (_needs_layout) {
        _layout();
        _needs_layout = false;
    }

    if (!_frame.size.is_negative())
        ui::config::drawer()->fill_rect(_absolute_frame, color);

    if (_image)
        _image->draw_in_rect(reinterpret_cast<decltype(this)>(_content_view)->_absolute_frame);

    _draw_subviews();
}

void ImageView::_layout() {
    View::_layout();

    switch (_content_mode) {
    case ContentMode::Fill:
        _content_view->set_frame({ _frame.size });
        break;
    case ContentMode::AspectFit:
        _content_view->set_frame(_frame.fit_size(_image->size()));
        _content_view->set_center(_frame.center());
        break;
    }

    reinterpret_cast<decltype(this)>(_content_view)->_layout();
}
