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

#include "ui.hpp"
#include "Rect.hpp"
#include "Event.hpp"
#include "Color.hpp"
#include "Touch.hpp"
#include "NonCopyable.hpp"


namespace ui {

    class Input;
    class FrameResizer;

    class View : cu::NonCopyable {

    public:

        using Array = std::vector<View*>;

    protected:

        Touch::ID _touch_id = 0;

        Rect _frame;
        View* _superview = nullptr;

        Array _subviews;

    public:

        bool clips = false;
        Point content_offset;
        Size content_size;

        bool is_hidden = false;
        bool draw_debug_frame = true;
        Color background_color;

    public:

        explicit View(const Rect& = { });
        virtual ~View();

    public:

        View* superview() const;
        const View::Array& subviews() const;

        void add_subview(View*);

        void remove_all_subviews();
        void remove_from_superview();

        void remove_last_subview();

    public:

        const Rect& frame() const;
        virtual Rect& edit_frame();

        const Rect& absolute_frame() const;

        Float content_width() const;
        Float content_height() const;

    public:

        void set_center(const Point&);

        void place_as_background();

        void place_at_center();
        void place_at_center_vertically();

        void place_at_bottom(Float margin = 0);

        void place_br(Float margin = 0);
        void place_bl(Float margin = 0);
        void place_tr(Float margin = 0);

        void place_at_left_half();
        void place_at_right_half();
        void place_at_top_half();
        void place_at_bottom_half();

        void stick_to(View* view, Edge edge, Float margin = 0, Edge alignment = Edge::Center);

    public:

        bool contains_global_point(const Point&) const;

        bool is_visible() const;

    public:

        virtual void _draw();

    private:

        bool _needs_resize = true;
        bool _needs_reposition = true;

        void _set_needs_resize();
        void _set_needs_reposition();

        Rect _absolute_frame;

        void _draw_rect();

        void _calculate_absolute_frame();

    protected:

        virtual void setup() { }

        virtual void layout_subviews() { };

    protected:

        friend Input;

        FrameResizer* _resizer = nullptr;
        bool _touch_enabled = false;
        bool _resize_enabled = false;

    public:

        cu::Event<Touch*> on_touch;

        void enable_touch();
        void disable_touch();

        void enable_resize();
        void disable_resize();

    public:

        static View* dummy(const Rect& = { 28, 28 });

    public:

        template <class T>
        void init_view(T*& view, const Rect& frame) {
            add_subview(view = new T(frame));
        }

        template <class T, class ...Args>
        void init_view(T*& view, const Args& ... args) {
            add_subview(view = new T(args ...));
        }

    };

}
