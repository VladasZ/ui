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

public:

    class Drawer {
    public:
        virtual ~Drawer();
        virtual void draw_in_rect(const Rect&) = 0;
    };

protected:

    void*   _data;
    Size    _size;
    Drawer* _drawer;
    uint8_t _channels;

public:

    explicit Image(const std::string& path);
    explicit Image(const Size& size, void* data, uint8_t channels);
    virtual ~Image();

    const Size& size()          const;
    void*       data()          const;
    uint8_t     channels()      const;
    bool        is_monochrome() const;

    void draw_in_rect(const Rect&);

protected:

    void _free_data();

};

};
