//
//  Image.hpp
//  ui
//
//  Created by Vladas Zakrevskis on 12/11/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include <string>

#include "Size.hpp"

namespace ui {

	class Image {

		void* _data = nullptr;
		Size _size;
		int _channels = 0;

	public:

		explicit Image(const std::string& path);
		~Image();

		const void* data() const;
		Size size() const;
		int channels() const;
	};
	
};
