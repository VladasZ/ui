//
//  Vector3.hpp
//  geometry
//
//  Created by Vladas Zakrevskis on 9/13/18.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

#include <string>

class Vector3 {
    
public:

	using Float = float;
    
    Float x = 0;
	Float y = 0;
	Float z = 0;
    
    Vector3() = default;
    Vector3(Float x, Float y, Float z);

	Float length() const;
    
	Vector3 cross(const Vector3& vec) const;
	Float dot(const Vector3& vec) const;

    Vector3& normalize();

	Vector3  operator -  (const Vector3& vec) const;
	Vector3& operator -= (const Vector3& vec);

	Vector3  operator *  (Float value) const;
	Vector3& operator *= (Float value);

	std::string to_string() const;
};

