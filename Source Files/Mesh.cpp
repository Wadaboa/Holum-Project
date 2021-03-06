//
//
//  Project : Holum
//  File Name : Mesh.cpp
//  Date : 04/01/2016
//
//

#include <Global.h>
#include <Mesh.h>

Mesh::Mesh(vector<vertex> vertices, vector<GLuint> indices, vector<texture> textures) {
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    init();
}

void Mesh::init() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), &vertices[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)0);
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, texCoords));
    glBindVertexArray(0);
}

void Mesh::draw(sh::Shader shader) {
    GLuint diffuseNr = 1;
    GLuint specularNr = 1;
    
    for(GLuint i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
		glUniform1i(glGetUniformLocation(shader.program, "tex"), 1);
        stringstream ss;
        string number;
        string name = textures[i].type;
		string materialType = "material.";
        
		if (name == "texture_diffuse") {
			ss << diffuseNr++;
			materialType += "diffuse";
		}
		else if (name == "texture_specular") {
			ss << specularNr++;
			materialType += "specular";
		}
        number = ss.str();
        glUniform1i(glGetUniformLocation(shader.program, materialType.c_str()), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
	if (textures.size() <= 0) {
		glUniform1i(glGetUniformLocation(shader.program, "tex"), 0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
    
    glUniform1f(glGetUniformLocation(shader.program, "material.shininess"), 16.0f);
    
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    for (GLuint i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

