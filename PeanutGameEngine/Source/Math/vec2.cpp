#include "vec2.h"

namespace peanut {
	namespace maths {
		vec2::vec2() {
			x = 0.0f;
			y = 0.0f;
		}

		vec2::vec2(const float& x, const float& y) {
			this->x = x;
			this->y = y;
		}

		vec2& vec2::add(const vec2& other) {
			x += other.x;
			y += other.y;
			return *this;
		}
		vec2& vec2::sub(const vec2& other) {
			x -= other.x;
			y -= other.y;
			return *this;
		}
		vec2& vec2::multiply(const vec2& other) {
			x *= other.x;
			y *= other.y;
			return *this;
		}
		vec2& vec2::divid(const vec2& other) {
			x /= other.x;
			y /= other.y;
			return *this;
		}

		vec2 operator+(vec2 left, const vec2& right) {
			return left.add(right);
		}

		vec2 operator-(vec2 left, const vec2& right) {
			return left.sub(right);
		}

		vec2 operator*(vec2 left, const vec2& right) {
			return left.multiply(right);
		}

		vec2 operator/(vec2 left, const vec2& right) {
			return left.divid(right);
		}

		vec2& vec2::operator+=(const vec2& other) {
			return add(other);
		}

		vec2& vec2::operator-=(const vec2& other) {
			return sub(other);
		}

		vec2& vec2::operator*=(const vec2& other) {
			return multiply(other);
		}

		vec2& vec2::operator/=(const vec2& other) {
			return divid(other);
		}

		bool vec2::operator==(const vec2& other) {
			return (x == other.x && y == other.y);
		}

		bool vec2::operator!=(const vec2& other) {
			return !(*this == other);
		}

		std::ostream& operator<<(std::ostream& stream, const vec2& vector) {
			stream << "vec2: (" << vector.x << ", " << vector.y << ")";
			return stream;
		}
	} 
}