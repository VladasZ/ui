//
//  Label.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/29/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include "Log.hpp"
#include "View.hpp"
#include "Font.hpp"


namespace ui {

    class Label : public View {

    private:

        std::string _text;
        View* _content_view;
        Font* _font;

    public:

        gm::Color text_color = gm::Color::white;

        Label(const Rect& frame = { });

    public:

        const std::string& text() const;
        void set_text(const std::string&);
        void set_font(Font*);

        template <class T>
        void set_text(const T& value) {
            set_text(cu::Log::to_string(value));
        }

    private:

        void _set_glyphs();

        void layout_subviews() override;

    };

}
