//
//  UIImage.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/11/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include <string>

#include "Rect.hpp"
#include "Image.hpp"

namespace ui {

class UIImage : public Image {

public:

    class Drawer {
    public:
        virtual ~Drawer();
        virtual void draw_in_rect(const Rect&) = 0;
    };

protected:

    Drawer* _drawer;

public:

    explicit UIImage(const std::string& path);
    explicit UIImage(void* data, const ::Size& size, uint8_t channels);

    const ::Size& size() const;

    void draw_in_rect(const Rect&);
};

};
