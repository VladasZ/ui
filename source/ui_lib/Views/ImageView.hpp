//
//  ImageView.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/11/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include "View.hpp"

namespace ui {

	class Image;

	class ImageView : public View {

		Image* _image = nullptr;

	public:

		ImageView(const Rect& rect, Image* image = nullptr);

		const Image* image() const;
		void set_image(Image* image);

	public:

		void draw() override;

	};

}