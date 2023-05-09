#pragma once
#include <string>
#include <vector>

#include "../glm/glm.hpp"
#include <GL/glew.h>

namespace peanut
{
    namespace graphics
    {
        class Shader;

        struct Vertex
        {
            glm::vec3 Position;
            glm::vec3 Normal;
            glm::vec3 Texture;
        };

        struct Texture
        {
            GLuint id;
            std::string type;
        };

        class Mesh
        {
        public:
            std::vector<Vertex>         vertices;
            std::vector<GLuint>   indices;
            std::vector<Texture>        textures;

            Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
            void Draw(Shader& shader);

        private:
            unsigned int VAO, VBO, EBO;

            void SetupMesh();
        };
    }
}


