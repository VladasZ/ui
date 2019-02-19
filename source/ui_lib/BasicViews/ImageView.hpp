//
//  ImageView.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/11/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include "View.hpp"
#include "UIImage.hpp"

namespace ui {

class ImageView : public View {

public:

    enum class ContentMode {
        Fill,
        AspectFit
    };

private:

    ContentMode _content_mode = ContentMode::Fill;
    UIImage* _image = nullptr;
    View* _content_view = nullptr;

public:

    ImageView(UIImage* = nullptr);
    ImageView(const Rect& = { }, UIImage* = nullptr);

    const UIImage* image() const;
    void set_image(UIImage*);
    void set_content_mode(ContentMode);

public:

    void _draw() override;

protected:

    void _layout() override;

};

}
