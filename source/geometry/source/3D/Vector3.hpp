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
    
    float x = 0;
    float y = 0;
    float z = 0;
    
    Vector3() = default;
    Vector3(float x, float y, float z);

    float length() const;
    
	Vector3 cross(const Vector3& vec) const;
	float dot(const Vector3& vec) const;

    Vector3& normalize();

	Vector3  operator -  (const Vector3& vec) const;
	Vector3& operator -= (const Vector3& vec);

	Vector3  operator *  (float value) const;
	Vector3& operator *= (float value);

	std::string to_string() const;
};

