#pragma once
#include <iostream>

namespace peanut {
	namespace maths {
		// vec4 is good for stuff like colors
		struct vec4 {
			float x, y, z, w;

			vec4() = default;
			vec4(const float& x, const float& y, const float& z, const float& w);

			vec4& add(const vec4& other);
			vec4& sub(const vec4& other);
			vec4& multiply(const vec4& other);
			vec4& divid(const vec4& other);

			friend vec4 operator+(vec4 left, const vec4& right);
			friend vec4 operator-(vec4 left, const vec4& right);
			friend vec4 operator*(vec4 left, const vec4& right);
			friend vec4 operator/(vec4 left, const vec4& right);

			vec4& operator+=(const vec4& other);
			vec4& operator-=(const vec4& other);
			vec4& operator*=(const vec4& other);
			vec4& operator/=(const vec4& other);

			bool operator==(const vec4& other);
			bool operator!=(const vec4& other);

			friend std::ostream& operator<<(std::ostream& stream, const vec4& vector);
		};


	} 
}