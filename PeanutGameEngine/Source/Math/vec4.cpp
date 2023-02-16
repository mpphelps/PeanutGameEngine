#include "vec4.h"

namespace peanut {
	namespace maths {

		vec4::vec4(const float& x, const float& y, const float& z, const float& w) {
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		vec4& vec4::add(const vec4& other) {
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;
			return *this;
		}
		vec4& vec4::sub(const vec4& other) {
			x -= other.x;
			y -= other.y;
			w += other.w;
			w += other.w;
			return *this;
		}
		vec4& vec4::multiply(const vec4& other) {
			x *= other.x;
			y *= other.y;
			w *= other.w;
			w *= other.w;
			return *this;
		}
		vec4& vec4::divid(const vec4& other) {
			x /= other.x;
			y /= other.y;
			w /= other.w;
			w /= other.w;
			return *this;
		}

		vec4 operator+(vec4 left, const vec4& right) {
			return left.add(right);
		}

		vec4 operator-(vec4 left, const vec4& right) {
			return left.sub(right);
		}

		vec4 operator*(vec4 left, const vec4& right) {
			return left.multiply(right);
		}

		vec4 operator/(vec4 left, const vec4& right) {
			return left.divid(right);
		}

		vec4& vec4::operator+=(const vec4& other) {
			return add(other);
		}

		vec4& vec4::operator-=(const vec4& other) {
			return sub(other);
		}

		vec4& vec4::operator*=(const vec4& other) {
			return multiply(other);
		}

		vec4& vec4::operator/=(const vec4& other) {
			return divid(other);
		}

		bool vec4::operator==(const vec4& other) {
			return (x == other.x && y == other.y && z == other.z && w == other.w);
		}

		bool vec4::operator!=(const vec4& other) {
			return !(*this == other);
		}

		std::ostream& operator<<(std::ostream& stream, const vec4& vector) {
			stream << "vec4: (" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
			return stream;
		}
	} 
}