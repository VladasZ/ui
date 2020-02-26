//
//  View.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/5/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include <vector>
#include <stdint.h>
#include <functional>

#include "Rect.hpp"
#include "Event.hpp"
#include "Color.hpp"
#include "Touch.hpp"


namespace ui {

    class Input;
    class ViewResizer;

    class View {

    public:

        using Array = std::vector<View*>;

    protected:

        Touch::ID _touch_id = 0;

        gm::Rect _frame;
        View* _superview = nullptr;

        View::Array _subviews;

        bool _needs_layout = true;

    public:

        bool clips = false;
        gm::Point content_offset;
        gm::Size content_size;

        bool is_hidden = false;
        bool draw_debug_frame = true;
        gm::Color background_color;

    public:

        explicit View(const gm::Rect& = { });
        virtual ~View();

    public:

        void add_subview(View*);
        void add_subviews(std::initializer_list<View*>);

        void remove_all_subviews();
        void remove_from_superview();

    public:

        View* superview() const;

    public:

        const gm::Rect& frame() const;
        gm::Rect& edit_frame();

        const gm::Rect& absolute_frame() const;

        void set_center(const gm::Point&);

        void place_at_center();

        void place_at_bottom(float margin = 0);

        void place_br(float margin = 0);
        void place_bl(float margin = 0);
        void place_tr(float margin = 0);

        float content_width() const;
        float content_height() const;

        void stick_to(View* view, gm::Edge edge, float margin = 0);

    public:

        gm::Point global_point_lo_local(const gm::Point&) const;
        bool contains_global_point(const gm::Point&) const;

        bool is_visible() const;

    public:

        virtual void _draw();

    protected:

        void _draw_rect();
        void _draw_subviews();

    protected:

        gm::Rect _absolute_frame;
        virtual void _layout();
        void _calculate_absolute_frame();
        void _layout_subviews();

        virtual void _setup() { }

    protected:

        friend Input;

        ViewResizer* _resizer = nullptr;
        bool _touch_enabled = false;
        bool _resize_enabled = false;

    public:

        cu::Event<Touch*> on_touch;

        void enable_touch();
        void disable_touch();

        void enable_resize();
        void disable_resize();

    public:

        static View* dummy(const gm::Rect& = { 28, 28 });


    public:

        template <class T>
        void init_view(T*& view, const gm::Rect& frame = { }) {
            add_subview(view = new T(frame));
        }

    };

}
