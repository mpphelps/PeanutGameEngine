#pragma once
#include <istream>

namespace peanut {
	namespace maths {

		struct vec2 {
			float x, y;
			vec2();
			vec2(const float& x, const float& y);

			vec2& add(const vec2& other);
			vec2& sub(const vec2& other);
			vec2& multiply(const vec2& other);
			vec2& divid(const vec2& other);

			friend vec2 operator+(vec2 left, const vec2& right);
			friend vec2 operator-(vec2 left, const vec2& right);
			friend vec2 operator*(vec2 left, const vec2& right);
			friend vec2 operator/(vec2 left, const vec2& right);

			vec2& operator+=(const vec2& other);
			vec2& operator-=(const vec2& other);
			vec2& operator*=(const vec2& other);
			vec2& operator/=(const vec2& other);

			bool operator==(const vec2& other);
			bool operator!=(const vec2& other);

			friend std::ostream& operator<<(std::ostream& stream, const vec2& vector);
		};


	} 
}