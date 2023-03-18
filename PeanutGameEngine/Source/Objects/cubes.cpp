#include "cubes.h"

namespace peanut {
	namespace objects {
		void Cubes::AddCube(glm::vec3 position)
		{
			positions.push_back(position);
		}
		glm::vec3 Cubes::GetPosition(int index) {
			if (index >= positions.size() || index < 0) {
				return glm::vec3(0.0f, 0.0f, 0.0f);
				std::cout << "Cubes index out of bounds" << std::endl;
			}
			else {
				return positions[index];
			}
			
		}
		int Cubes::Count() {
			return positions.size();
		}
	}
}

