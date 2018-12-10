//
//  Vector3.cpp
//  geometry
//
//  Created by Vladas Zakrevskis on 9/13/18.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#include <math.h>

#include "Vector3.hpp"


Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) { }

float Vector3::length() const {
    return static_cast<float>(sqrt(x * x + y * y + z * z));
}

Vector3 Vector3::cross(const Vector3& vec) const {
	return {
		y * vec.z - z * vec.y, 
		z * vec.x - x * vec.z,
		x * vec.y - y * vec.x
	};
}

float Vector3::dot(const Vector3& vec) const {
	return x * vec.x + y * vec.y + z * vec.z;
}

Vector3& Vector3::normalize() {
    auto ratio = 1 / length();
    return this->operator*=(ratio);
}

Vector3 Vector3::operator - (const Vector3& vec) const {
	return {
		x - vec.x,
		y - vec.y,
		z - vec.z
	};
}

Vector3& Vector3::operator -= (const Vector3& vec) {
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	return *this;
}

Vector3 Vector3::operator * (float value) const {
	return {
		x * value,
		y * value,
		z * value
	};
}

Vector3& Vector3::operator *= (float value) {
	x *= value;
	y *= value;
	z *= value;
	return *this;
}

std::string Vector3::to_string() const {
	return std::string() + "[ " + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + " ]";
}
