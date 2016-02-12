//
//
//  Project : Holum
//  File Name : Model.cpp
//  Date : 04/02/2016
//
//

#include <Global.h>
#include <Model.h>

Model::Model() {
    MAX = 0;
    MIN = 99999;
}

Model::Model(GLchar* path) {
    MAX = 0;
    MIN = 99999;
	loadModel(path);
}

void Model::draw(sh::Shader shader) {
	for(GLuint i = 0; i < meshes.size(); i++)
		meshes[i].draw(shader);
}

GLint Model::textureFromFile(const char* path) {
	string filename = string(path);
    filename = directory + '/' + filename;
    
    GLuint textureID;
    glGenTextures(1, &textureID);
    
    int imageWidth, imageHeight;
    int channels = 0;
    unsigned char* image = SOIL_load_image(filename.c_str(), &imageWidth, &imageHeight, &channels, SOIL_LOAD_RGB);
    
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(image);
    
    return textureID;
}

void Model::loadModel(string path) {
	Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);
	
    if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		cout << "Errore 013: Caricamento file OBJ non riuscito." << endl << importer.GetErrorString();
		return;
	}
	
	directory = path.substr(0, path.find_last_of('/'));
    
	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene) {
	for(GLuint i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]]; 
		meshes.push_back(processMesh(mesh, scene));
	}
    
	for(GLuint i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
    vector<Mesh::vertex> vertices;
	vector<GLuint> indices;
	vector<Mesh::texture> textures;

	for(GLuint i = 0; i < mesh->mNumVertices; i++) {
		Mesh::vertex vertex;
		vec3 tempVector;
        
		tempVector.x = mesh->mVertices[i].x;
		tempVector.y = mesh->mVertices[i].y;
		tempVector.z = mesh->mVertices[i].z;
		vertex.position = tempVector;
        
        if (tempVector.y >= MAX) {
            MAX = tempVector.y;
        }
        if (tempVector.y <= MIN) {
            MIN = tempVector.y;
        }
        
        if(mesh->mNormals) {
            tempVector.x = mesh->mNormals[i].x;
            tempVector.y = mesh->mNormals[i].y;
            tempVector.z = mesh->mNormals[i].z;
            vertex.normal = tempVector;
        }
        else {
            vertex.normal = vec3(0.0f, 0.0f, 0.0f);
        }
		
		if(mesh->mTextureCoords[0]) {
			vec2 tempVec;
			tempVec.x = mesh->mTextureCoords[0][i].x;
			tempVec.y = mesh->mTextureCoords[0][i].y;
			vertex.texCoords = tempVec;
		}
        else {
			vertex.texCoords = vec2(0.0f, 0.0f);
        }
        
		vertices.push_back(vertex);
	}
	
	for(GLuint i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for(GLuint j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	
	if(mesh->mMaterialIndex > 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        
		vector<Mesh::texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		vector<Mesh::texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}
	
	return Mesh(vertices, indices, textures);
}

vector<Mesh::texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
{
    vector<Mesh::texture> textures;
    for(GLuint i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        GLboolean skip = false;
        for(GLuint j = 0; j < loadedTextures.size(); j++) {
            if(loadedTextures[j].path == str) {
                textures.push_back(loadedTextures[j]);
                skip = true;
                break;
            }
        }
        if(!skip) {
            Mesh::texture texture;
            texture.id = textureFromFile(str.C_Str());
            texture.type = typeName;
            texture.path = str;
            textures.push_back(texture);
            loadedTextures.push_back(texture);
        }
    }
    return textures;
}