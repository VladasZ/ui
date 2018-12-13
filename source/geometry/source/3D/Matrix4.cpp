//
//  Matrix4.cpp
//  geometry
//
//  Created by Vladas Zakrevskis on 9/13/18.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#include <math.h>
#include <algorithm>

#include "Matrix4.hpp"


Matrix4::Matrix4() : Matrix4 {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
} { }

Matrix4::Matrix4(Float value) {
	for (int i = 0; i < Matrix4::size; i++)
		*(&data[0][0] + i) = value;
}

Matrix4::Matrix4(const std::initializer_list<Float>& list) {
    if (list.size() != Matrix4::size)
        throw "Matrix4 invalid initializer";
    std::copy(list.begin(), list.end(), &data[0][0]);
}

Matrix4 Matrix4::operator *(const Matrix4& mat) const {
	Matrix4 res;
	res.data[0][0] = data[0][0] * mat.data[0][0] + data[0][1] * mat.data[1][0] + data[0][2] * mat.data[2][0] + data[0][3] * mat.data[3][0];
	res.data[0][1] = data[0][0] * mat.data[0][1] + data[0][1] * mat.data[1][1] + data[0][2] * mat.data[2][1] + data[0][3] * mat.data[3][1];
	res.data[0][2] = data[0][0] * mat.data[0][2] + data[0][1] * mat.data[1][2] + data[0][2] * mat.data[2][2] + data[0][3] * mat.data[3][2];
	res.data[0][3] = data[0][0] * mat.data[0][3] + data[0][1] * mat.data[1][3] + data[0][2] * mat.data[2][3] + data[0][3] * mat.data[3][3];

	res.data[1][0] = data[1][0] * mat.data[0][0] + data[1][1] * mat.data[1][0] + data[1][2] * mat.data[2][0] + data[1][3] * mat.data[3][0];
	res.data[1][1] = data[1][0] * mat.data[0][1] + data[1][1] * mat.data[1][1] + data[1][2] * mat.data[2][1] + data[1][3] * mat.data[3][1];
	res.data[1][2] = data[1][0] * mat.data[0][2] + data[1][1] * mat.data[1][2] + data[1][2] * mat.data[2][2] + data[1][3] * mat.data[3][2];
	res.data[1][3] = data[1][0] * mat.data[0][3] + data[1][1] * mat.data[1][3] + data[1][2] * mat.data[2][3] + data[1][3] * mat.data[3][3];

	res.data[2][0] = data[2][0] * mat.data[0][0] + data[2][1] * mat.data[1][0] + data[2][2] * mat.data[2][0] + data[2][3] * mat.data[3][0];
	res.data[2][1] = data[2][0] * mat.data[0][1] + data[2][1] * mat.data[1][1] + data[2][2] * mat.data[2][1] + data[2][3] * mat.data[3][1];
	res.data[2][2] = data[2][0] * mat.data[0][2] + data[2][1] * mat.data[1][2] + data[2][2] * mat.data[2][2] + data[2][3] * mat.data[3][2];
	res.data[2][3] = data[2][0] * mat.data[0][3] + data[2][1] * mat.data[1][3] + data[2][2] * mat.data[2][3] + data[2][3] * mat.data[3][3];

	res.data[3][0] = data[3][0] * mat.data[0][0] + data[3][1] * mat.data[1][0] + data[3][2] * mat.data[2][0] + data[3][3] * mat.data[3][0];
	res.data[3][1] = data[3][0] * mat.data[0][1] + data[3][1] * mat.data[1][1] + data[3][2] * mat.data[2][1] + data[3][3] * mat.data[3][1];
	res.data[3][2] = data[3][0] * mat.data[0][2] + data[3][1] * mat.data[1][2] + data[3][2] * mat.data[2][2] + data[3][3] * mat.data[3][2];
	res.data[3][3] = data[3][0] * mat.data[0][3] + data[3][1] * mat.data[1][3] + data[3][2] * mat.data[2][3] + data[3][3] * mat.data[3][3];
	return res;
}

Matrix4& Matrix4::operator *=(const Matrix4& mat) {
    return *this = this->operator*(mat);
}

std::string Matrix4::to_string() const {
	std::string result;

	static const uint8_t row_count = static_cast<uint8_t>(sqrt(Matrix4::size));

	for (int i = 0; i < Matrix4::size; i++) {
		if (i % row_count == 0)
			result += "\n";
		result += std::to_string(*(&data[0][0] + i)) + " ";
	}

	return result;
}

Matrix4 Matrix4::scale(Float scale) {
	return  {
		scale,     0,     0, 0,
			0, scale,     0, 0,
			0,     0, scale, 0,
			0,     0,     0, 1
	};
}
 
Matrix4 Matrix4::translation(const Vector3& location) {
	return {
		         1,		     0,			 0, 0,
		         0,			 1,			 0, 0,
				 0,		     0,			 1, 0,
		location.x, location.y, location.z, 1
	};
}

Matrix4 Matrix4::rotation(Float angle, const Vector3& in) {
    return {};//glm::rotate(glm::mat4(), angle, {in.x, in.y, in.z});
}

Matrix4 Matrix4::perspective(Float fovy, Float aspect, Float zNear, Float zFar) {

	Float const tan_half_fovy = tan(fovy / 2.0f);

	Matrix4 result(0.0f);
	result.data[0][0] = 1.0f / (aspect * tan_half_fovy);
	result.data[1][1] = 1.0f / (tan_half_fovy);
	result.data[2][3] = -1.0f;

	result.data[2][2] = -(zFar + zNear) / (zFar - zNear);
	result.data[3][2] = -(2.0f * zFar * zNear) / (zFar - zNear);

	return result;
}
