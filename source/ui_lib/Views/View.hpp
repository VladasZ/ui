//
//  View.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/5/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include <stdint.h>
#include <vector>

#include "Rect.hpp"
#include "Color.hpp"

namespace ui {
  
  class View {

  public:

	  enum class Edge : uint8_t {
		  Top         = 0b00000001,
		  Bottom      = 0b00000010,
		  Left        = 0b00000100,
		  Right       = 0b00001000,
		  TopLeft     = Top    | Left,
		  TopRight    = Top    | Right,
		  BottomLeft  = Bottom | Left,
		  BottomRight = Bottom | Right,
		  None        = 0
	  };

  private:

	  struct EdgeInfo {

		  inline static const float width = 16;

		  float left_min = 0;
		  float left_max = 0;

		  float right_min = 0;
		  float right_max = 0;

		  float top_min = 0;
		  float top_max = 0;

		  float bottom_min = 0;
		  float bottom_max = 0;
	  };

	  EdgeInfo _edge_info;

  protected:

	  bool _needs_layout = true;
	  Rect _frame;
	  View* _superview = nullptr;
	  std::vector<View*> _subviews;

  public:

	  Color color;

	  View(const Rect& rect = { });
	  virtual ~View();

	  void add_subview(View* view);

  public:

	  void set_frame(const Rect& frame);
	  void set_origin(const Point& origin);
	  void set_center(const Point& center);

  public:

	  virtual void draw();
	  Edge get_edge(const Point& point) const;

  protected:

	  Rect _absolute_frame;
	  virtual void _layout();

  };
}
