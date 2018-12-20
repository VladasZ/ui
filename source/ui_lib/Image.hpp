//
//  Image.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/11/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include <string>

#include "Rect.hpp"

namespace ui {

class Image {

protected:

    void* _data = nullptr;
    Size _size;
    int _channels = 0;

public:

    explicit Image(const std::string& path);
    explicit Image(const Size& size, void* data, int channels);
    virtual ~Image();

    const Size& size() const;

    bool is_monochrome() const;

    virtual void draw_in_rect(const Rect& rect) = 0;

protected:

    void _free_data();

};

};
