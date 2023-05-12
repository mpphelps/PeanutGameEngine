#pragma once
#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>

#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../Utils/stb_image.h"

#include "../../../Dependencies/ASSIMP/include/assimp/Importer.hpp"
#include "../../../Dependencies/ASSIMP/include/assimp/scene.h"
#include "../../../Dependencies/ASSIMP/include/assimp/postprocess.h"

#include "mesh.h"
#include "shader.h"

#include <vector>

namespace peanut
{
    namespace graphics
    {

        unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);


        class Model
        {
        public:
            // model data 
            std::vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
            std::vector<Mesh>    meshes;
            std::string directory;
            bool gammaCorrection;

            // constructor, expects a filepath to a 3D model.
            Model(std::string const& path, bool gamma = false) : gammaCorrection(gamma)
            {
                LoadModel(path);
            }
            void Draw(Shader& shader);
        private:
            

            void LoadModel(std::string path);
            void ProcessNode(aiNode* node, const aiScene* scene);
            Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
            std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

        };

    }
}

#endif