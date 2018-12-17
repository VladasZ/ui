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

	public:

        enum class ContentMode : uint64_t {
			Fill,
			AspectFit
		};

	private:

		ContentMode _content_mode = ContentMode::Fill;
		Image* _image = nullptr;
		View* _content_view = nullptr;

	public:

		ImageView(const Rect& rect, Image* image = nullptr);

		const Image* image() const;
		void set_image(Image* image);
		void set_content_mode(ContentMode mode);

	public:

		void draw() override;

	protected:

		void _layout() override;

	};

}
