//
//  View.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/5/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include <array>
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

        float content_width() const;
        float content_height() const;

    public:

        void set_center(const Point&);

        void place_as_background();

        void place_at_center();
        void center_vertically();
        void center_horizontally();

        void place_at_bottom(float margin = 0);

        void place_l(float margin = 0);
        void place_r(float margin = 0);

        void place_br(float margin = 0);
        void place_bl(float margin = 0);
        void place_tr(float margin = 0);

        void place_at_left_half(bool preserve_height = false);
        void place_at_right_half(bool preserve_height = false);
        void place_at_top_half();
        void place_at_bottom_half();

		void same_height(View*);

        template <class Container>
        void place_array_hor(const Container& container) {
            auto width = _frame.size.width / container.size();
            for (int i = 0; i < container.size(); i++)
                container[i]->edit_frame() = { i * width, 0, width, _frame.size.height };
        }

		template <class ...Views, size_t size = sizeof...(Views)>
		void place_hor(Views& ... views) {
			auto width = _frame.size.width / size;
			auto tuple = std::forward_as_tuple(views...);
			cu::static_for<size>([&](auto i) {
				std::get<i>(tuple)->edit_frame() =
				{ i * width, 0, width, _frame.size.height };
			});
		}

		template <class ...Views, size_t size = sizeof...(Views)>
		void place_hor(const std::array<float, size>& ratio, Views& ... views) {
			auto tuple = std::forward_as_tuple(views...);
			auto total_ratio = 1.0f / std::accumulate(ratio.begin(), ratio.end(), 0.0f);
			cu::static_for<size>([&](auto i) {
				constexpr bool is_first = i == 0;
				auto x_pos = is_first ? 0 : std::get<is_first ? 0 : i - 1>(tuple)->frame().max_x();
				std::get<i>(tuple)->edit_frame() = 
				{ x_pos, 0, ratio[i] * _frame.size.width * total_ratio, _frame.size.height };
			});
		}

		template <class ...Views, size_t size = sizeof...(Views)>
		void place_ver(Views&... views) {
            auto height = _frame.size.height / size;
			auto tuple = std::forward_as_tuple(views...);
            cu::static_for<size>([&](auto i) {
                std::get<i>(tuple)->edit_frame() =
				{ 0, i * height, _frame.size.width, height, };
            });
        }

		template <class ...Views, size_t size = sizeof...(Views)>
		void place_ver(const std::array<float, size>& ratio, Views& ... views) {
            auto tuple = std::forward_as_tuple(views...);
			auto total_ratio = 1.0f / std::accumulate(ratio.begin(), ratio.end(), 0.0f);
            cu::static_for<size>([&](auto i) {
                constexpr bool is_first = i == 0;
                auto y_pos = is_first ? 0 : std::get<is_first ? 0 : i - 1>(tuple)->frame().max_y();
                std::get<i>(tuple)->edit_frame() =
				{ 0, y_pos, _frame.size.width, ratio[i] * _frame.size.height * total_ratio, };
            });
        }

        void stick_to(View* view, Edge edge, float margin = 0, Edge alignment = Edge::Center);

    public:

        bool contains_global_point(const Point&) const;

        bool is_visible() const;

    public:

        virtual void _draw();

    private:

        bool _needs_layout = true;
        bool _needs_reposition = true;

    protected:

        void _set_needs_layout();
        void _set_needs_reposition();

    private:

        Rect _absolute_frame;

        void _draw_rect();

        void _calculate_absolute_frame();

    protected:

        virtual void setup() { }

        virtual void layout() { };

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
