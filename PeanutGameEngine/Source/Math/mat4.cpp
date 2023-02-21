#include "mat4.h"

namespace peanut {
	namespace maths {
		mat4::mat4() {
			for (int i = 0; i < 4 * 4; i++) {
				elements[i] = 0.0f;
			}
		}

		mat4::mat4(float diagonal) {
			for (int i = 0; i < 4 * 4; i++) {
				elements[i] = 0.0f;
			}
			elements[0 + 0 * 4] = diagonal;
			elements[1 + 1 * 4] = diagonal;
			elements[2 + 2 * 4] = diagonal;
			elements[3 + 3 * 4] = diagonal;
		}

		mat4 mat4::identity() {
			return mat4(1.0f);
		}

		mat4& mat4::multiply(const mat4& other) {
			// Perform multiplication in column major ordering
			// This is for OpenGL
			// e[row + col * 4]
			for (int x = 0; x < 4; x++) {
				for (int y = 0; y < 4; y++) {
					float sum = 0.0f;
					for (int e = 0; e < 4; e++) {
						sum += elements[x + e * 4] * other.elements[e + y * 4];
					}
					this->elements[x + y * 4] = sum;
				}
			}

			return *this;
		}

		vec4 mat4::multiply(vec4& other) {
			vec4 result;
			result.x = this->elements[0 + 0 * 4] * other.x +
				this->elements[0 + 1 * 4] * other.y +
				this->elements[0 + 2 * 4] * other.z +
				this->elements[0 + 3 * 4] * other.w;
			result.y = this->elements[1 + 0 * 4] * other.x +
				this->elements[1 + 1 * 4] * other.y +
				this->elements[1 + 2 * 4] * other.z +
				this->elements[1 + 3 * 4] * other.w;
			result.z = this->elements[2 + 0 * 4] * other.x +
				this->elements[2 + 1 * 4] * other.y +
				this->elements[2 + 2 * 4] * other.z +
				this->elements[2 + 3 * 4] * other.w;
			result.w = this->elements[3 + 0 * 4] * other.x +
				this->elements[3 + 1 * 4] * other.y +
				this->elements[3 + 2 * 4] * other.z +
				this->elements[3 + 3 * 4] * other.w;
			return result;
		}

		vec4 operator*(mat4 left, vec4& right) {
			return left.multiply(right);
		}

		mat4 operator*(mat4 left, const mat4& right) {
			return left.multiply(right);
		}

		mat4& mat4::operator*=(const mat4& other) {
			return multiply(other);
		}


		mat4 mat4::orthographic(float left, float right, float bottom, float top, float near, float far) {
			// Cherno initialized everything to 1, and didn't have any 0s, but this is more in line with what's online
			mat4 result(0.0f);

			result.elements[3 + 3 * 4] = 1.0f;

			result.elements[0 + 0 * 4] = 2.0f / (right - left);
			result.elements[1 + 1 * 4] = 2.0f / (top - bottom);
			result.elements[2 + 2 * 4] = 2.0f / (near - far);

			result.elements[0 + 3 * 4] = (left + right) / (left - right);
			result.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
			result.elements[2 + 3 * 4] = (far + near) / (far - near);

			return result;
		}

		mat4 mat4::perspective(float fov, float aspectRatio, float near, float far) {
			mat4 result(0.0f);

			result.elements[0 + 0 * 4] = 1.0f / (aspectRatio * tan(toRadians(fov) / 2));
			result.elements[1 + 1 * 4] = 1.0f / (tan(toRadians(fov) / 2));
			result.elements[2 + 2 * 4] = -(far + near)/(far - near);

			result.elements[2 + 3 * 4] = -(2.0f * far * near) / (far - near);

			result.elements[3 + 2 * 4] = -1.0f;

			return result;
		}

		mat4 mat4::translation(const vec3& translation) {
			mat4 result(0.0f);

			result.elements[0 + 0 * 4] = 1.0f;
			result.elements[1 + 1 * 4] = 1.0f;
			result.elements[2 + 2 * 4] = 1.0f;
			result.elements[3 + 3 * 4] = 1.0f;

			result.elements[0 + 3 * 4] = translation.x;
			result.elements[1 + 3 * 4] = translation.y;
			result.elements[2 + 3 * 4] = translation.z;

			return result;
		}

		mat4 mat4::rotation(float angle, const vec3& axis) {
			mat4 result(0.0f);

			float radians = toRadians(angle);
			float c = cos(radians);
			float s = sin(radians);
			float omc = 1.0f - c;

			float x = axis.x;
			float y = axis.y;
			float z = axis.z;

			result.elements[0 + 0 * 4] = c + pow(x,2) * omc;
			result.elements[1 + 0 * 4] = y * x * omc + z * s;
			result.elements[2 + 0 * 4] = z * x * omc - y * s;

			result.elements[0 + 1 * 4] = x * y * omc - z * s;
			result.elements[1 + 1 * 4] = c + pow(y,2) * omc;
			result.elements[2 + 1 * 4] = z * y * omc + x * s;

			result.elements[0 + 2 * 4] = x * z * omc + y * s;
			result.elements[1 + 2 * 4] = y * z * omc - x * s;
			result.elements[2 + 2 * 4] = c + pow(z,2) * omc;

			return result;
		}

		mat4 mat4::scale(const vec3& scale) {
			mat4 result(0.0f);

			result.elements[0 + 0 * 4] = scale.x;
			result.elements[1 + 1 * 4] = scale.y;
			result.elements[2 + 2 * 4] = scale.z;
			result.elements[3 + 3 * 4] = 1.0f;

			return result;

		}
	}
}