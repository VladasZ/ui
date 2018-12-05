//
//  View.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/5/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#include <vector>

#include "Rect.hpp"

namespace ui {
  
  class View {

	  Rect _frame;
	  View* _superview = nullptr;
	  std::vector<View*> _subviews;

  public:

	  View(const Rect& rect);
	  virtual ~View();

	  void add_subview(View* view);

  public:
	  virtual void draw();

  private:

	  Rect _absolute_frame;
	  void _calculate_absolute_frame();

  };
}
