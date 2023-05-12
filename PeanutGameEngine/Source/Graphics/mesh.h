#pragma once
#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"

#include "shader.h"

#include <string>
#include <vector>

#define MAX_BONE_INFLUENCE 4

namespace peanut
{
    namespace graphics
    {
        class Shader;

        struct Vertex {
            // position
            glm::vec3 Position;
            // normal
            glm::vec3 Normal;
            // texCoords
            glm::vec2 TexCoords;
            // tangent
            glm::vec3 Tangent;
            // bitangent
            glm::vec3 Bitangent;
            //bone indexes which will influence this vertex
            int m_BoneIDs[MAX_BONE_INFLUENCE];
            //weights from each bone
            float m_Weights[MAX_BONE_INFLUENCE];
        };

        struct Texture
        {
            GLuint id;
            std::string type;
            std::string path;
        };

        class Mesh
        {
        public:
            std::vector<Vertex>   vertices;
            std::vector<GLuint>   indices;
            std::vector<Texture>  textures;

            Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
            void Draw(Shader& shader);

        private:
            unsigned int VAO, VBO, EBO;

            void SetupMesh();
        };
    }
}

#endif
