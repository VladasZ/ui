//
//  Matrix4.hpp
//  geometry
//
//  Created by Vladas Zakrevskis on 9/13/18.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

#include <cstring>
#include <string> 

#include <initializer_list>

#include "Vector3.hpp"

class Matrix4 {
    
public:

	using Float = float;
    
    static const size_t size = 16;
    
	Float data[4][4];
    
    Matrix4();
	Matrix4(Float value);
    Matrix4(const std::initializer_list<Float>& list);
    
    template <class CompatibleClass>
    Matrix4(const CompatibleClass& obj) {
        static_assert(sizeof(Matrix4) == sizeof(CompatibleClass), "Matrix4 invalid initializer");
		std::memcpy(&data[0][0], static_cast<void*>(&obj), sizeof(Matrix4));
    }
    
    Matrix4  operator * (const Matrix4& mat) const;
    Matrix4& operator *=(const Matrix4& mat);

	Vector3  operator * (const Vector3& vec) const;

	std::string to_string() const;

	static Matrix4 scale(Float scale);
	static Matrix4 translation(const Vector3& location);
    static Matrix4 rotation(Float angle, const Vector3& axis);
	static Matrix4 perspective(Float fovy, Float aspect, Float zNear, Float zFar);

};
