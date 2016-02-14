//
//
//  Project : Holum
//  File Name : Model.h
//  Date : 04/02/2016
//
//

#pragma once

#include <Mesh.h>

class Model {
    public:
        float MAX;
        float MIN;
    
        Model();
        Model(GLchar* path);
        void draw(sh::Shader shader);
        
    private:
        vector<Mesh> meshes;
        vector<Mesh::texture> loadedTextures;
        string directory;
    
        void loadModel(string path);
        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);
        GLint textureFromFile(const char* path);
        vector<Mesh::texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};
