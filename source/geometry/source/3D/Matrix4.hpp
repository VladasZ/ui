//
//  Matrix4.hpp
//  geometry
//
//  Created by Vladas Zakrevskis on 9/13/18.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

#include <cstring> 

#include <initializer_list>

#include "Vector3.hpp"

class Matrix4 {
    
public:
    
    static const size_t size = 16;
    
    float data[4][4];
    
    Matrix4();
	Matrix4(float value);
    Matrix4(const std::initializer_list<float>& list);
    
    template <class CompatibleClass>
    Matrix4(const CompatibleClass& obj) {
        static_assert(sizeof(Matrix4) == sizeof(CompatibleClass), "Matrix4 invalid initializer");
		std::memcpy(&data[0][0], static_cast<void*>(&obj), sizeof(Matrix4));
    }
    
    Matrix4  operator * (const Matrix4& mat) const;
    Matrix4& operator *=(const Matrix4& mat);

	static Matrix4 scale(float scale);
	static Matrix4 translation(const Vector3& location);
    static Matrix4 rotation(float angle, const Vector3& axis);
	static Matrix4 perspective(float fovy, float aspect, float zNear, float zFar);

};
