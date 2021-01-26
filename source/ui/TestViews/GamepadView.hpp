//
//  GamepadView.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 26/01/21.
//  Copyright © 2021 VladasZ. All rights reserved.
//

#pragma once

#include "Label.hpp"
#include "Slider.hpp"
#include "AnalogStickView.hpp"


namespace ui {

	class GamepadView : public View {

	public:

	private:

		View* up;
		View* down;
		View* left;
		View* right;

		View* a;
		View* b;
		View* x;
		View* y;

		View* left_kok;
		View* right_kok;

		AnalogStickView* left_stick;
		AnalogStickView* right_stick;




	};

}
