//
//
//  Project : Holum
//  File Name : Mesh.h
//  Date : 04/01/2016
//
//

#pragma once

#include <Shader.h>

/*!
 * \class Mesh
 * \brief The Mesh class defines each single drawable entity, in a format that OpenGL uses to render the objects.
 */
class Mesh {
	private:
		/*!
		 * The so called vertex array object (VAO) can be bound just like a vertex buffer object 
		 * and any subsequent vertex attribute calls from that point on will be stored inside the VAO. 
		 *
		 * This has the advantage that when configuring vertex attribute pointers you only have to make those calls once
		 * and whenever we want to draw the object, we can just bind the corresponding VAO. 
		 * This makes switching between different vertex data and attribute configurations as easy as binding a different VAO.
		 *
		 * __Core OpenGL requires that we use a VAO so it knows what to do with our vertex inputs. 
		 * If we fail to bind a VAO, OpenGL will most likely refuse to draw anything.__
		 *
		 * A vertex array object stores the following:
		 *
		 * * Calls to glEnableVertexAttribArray or glDisableVertexAttribArray.
		 * * Vertex attribute configurations via glVertexAttribPointer.
		 * * Vertex buffer objects associated with vertex attributes by calls to glVertexAttribPointer.
		 * 
		 */
		GLuint VAO;

		/*!
		 * The so called vertex buffer objects (VBO) can store a large number of vertices in the GPU's memory. 
		 *
		 * The advantage of using those buffer objects is that we can send large batches of data all at once to the graphics card,
		 * without having to send data a vertex a time. 
		 * Sending data to the graphics card from the CPU is relatively slow, 
		 * so wherever we can we try to send as much data as possible at once. 
		 * Once the data is in the graphics card's memory
		 * the vertex shader has almost instant access to the vertices making it extremely fast.
		 * 
		 */
		GLuint VBO;

		/*! An EBO is a buffer, just like a vertex buffer object, that stores indices that OpenGL uses to decide what vertices to draw. */
		GLuint EBO;
		
		/*!
		 * This initialization function is used to setup the appropriate buffers 
		 * and specify the vertex shader layout via vertex attribute pointers.
		 * 
		 * It is called after the constructor, which provides us large lists of mesh data that we can use for rendering.
		 */
		void init();
    
	public:
		/*!
		 * \struct vertex
		 * \brief It is a set of vectors which contains a position vector, a normal vector and a texture coordinate vector.
		 */
		typedef struct {
			/*! The actual point represented in the tridimensional space (x, y, z). */
			vec3 position;

			/*!	
			 * When lighting is enabled in OpenGL, 
			 * the normal vectors are used to determine how much light is received at the specified vertex or surface.
			 * 
			 * This lighting processing is performed at eye coordinate space, 
			 * therefore, normal vectors in object coordinates are also transformed to eye coordinates with GL_MODELVIEW matrix,
			 * but in a different way as vertices do.
			 */
			vec3 normal;

			/*! Texture coordinates specify the point in the texture image that will correspond to the vertex you are specifying them for. */
			vec2 texCoords;
		} vertex;

		/*!
		 * \struct texture
		 * \brief It is used to organize the material data, in the form of textures.
		 */
		typedef struct {
			/*! The id of the texture, which is just an incremental identifier. */
			GLuint id;

			/*! The type of the texture (e.g. a diffuse texture or a specular texture). */
			string type;

			/*! The actual path of a particular texture. */
			aiString path;
		} texture;
        
        /*! The set of vertices which defines a particular mesh. */
		vector<vertex> vertices;

		/*! The set of indices which defines a particular mesh. */
		vector<GLuint> indices;

		/*! The set of textures which defines a particular mesh. */
		vector<texture> textures;

		/*! The constructor loads Assimp's data structures and transforms that data to a format that OpenGL understands. */
		Mesh(vector<vertex> vertices, vector<GLuint> indices, vector<texture> textures);

		/*! It renders the mesh, after binding the appropriate textures. */
		void draw(sh::Shader shader);
};