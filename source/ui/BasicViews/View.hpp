//
//  View.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/5/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include <vector>
#include <numeric>
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
        void center_vertically();
        void center_horizontally();

        void place_at_bottom(Float margin = 0);

        void place_br(Float margin = 0);
        void place_bl(Float margin = 0);
        void place_tr(Float margin = 0);

        void place_at_left_half();
        void place_at_right_half();
        void place_at_top_half();
        void place_at_bottom_half();

//        template <class ...Views>
//        void distribute_horizontally(Views&&... args) {
//            constexpr auto size = sizeof...(Views);
//            auto width = _frame.size.width / size;
//
//            cu::static_for<0, size>([&](auto index) {
//                std::get<index.value>(std::forward_as_tuple(args...))->edit_frame() =
//                        { index.value * width,
//                          0,
//                          width,
//                          _frame.size.height
//                        };
//            });
//        }

        template <class Container>
        void distribute_horizontally(const Container& container) {
            auto width = _frame.size.width / container.size();

            for (int i = 0; i < container.size(); i++) {
                container[i]->edit_frame() =
                        { i * width,
                          0,
                          width,
                          _frame.size.height
                        };
            }

        }



        template <class ...Views>
        void distribute_vertically(Views&&... args) {
            constexpr auto size = sizeof...(Views);
            auto height = _frame.size.height / size;

            cu::static_for<0, size>([&](auto index) {
                std::get<index.value>(std::forward_as_tuple(args...))->edit_frame() =
                        { 0,
                          index.value * height,
                          _frame.size.width,
                          height,
                        };
            });

        }

        template <class ...Args>
        void distribute_vertically_with_ratio(std::vector<float> ratio, Args&&... args) {

            constexpr auto size = sizeof...(Args);
            auto tuple = std::forward_as_tuple(args...);

            cu::static_for<0, size>([&](auto index) {
                constexpr auto i = index.value;
                constexpr bool is_first = i == 0;
                auto prev_max_y = std::get<is_first ? 0 : i - 1>(tuple)->frame().max_y();
                std::get<i>(tuple)->edit_frame() =
                        { 0,
                          is_first ? 0 : prev_max_y,
                          _frame.size.width,
                          ratio[i] * _frame.size.height * (1.0f / std::accumulate(ratio.begin(), ratio.end(), 0.0f)),
                        };
            });

        }

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
        T* init_view(T*& view, const Rect& frame) {
            add_subview(view = new T(frame));
            return view;
        }

        template <class T, class ...Args>
        T* init_view(T*& view, Args&&... args) {
            add_subview(view = new T(std::forward<Args>(args) ...));
            return view;
        }

    };

}
