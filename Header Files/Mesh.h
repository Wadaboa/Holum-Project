//
//
//  Project : Holum
//  File Name : Mesh.h
//  Date : 04/01/2016
//
//

#pragma once

#include <Shader.h>

class Mesh {
	private:
		GLuint VAO, VBO, EBO;
		
		void init();
    
	public:
		typedef struct {
			vec3 position;
			vec3 normal;
			vec2 texCoords;
		} vertex;

		typedef struct {
			GLuint id;
			string type;
			aiString path;
		} texture;
        
		vector<vertex> vertices;
		vector<GLuint> indices;
		vector<texture> textures;

		Mesh(vector<vertex> vertices, vector<GLuint> indices, vector<texture> textures);
		void draw(sh::Shader shader);
};