#pragma once
#include "CommonHeaders.h"

#include "Shader.h"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	unsigned int id;
	std::string type;  //diffuse or specular, advanced topic
};

class Mesh {
	public:
		//mesh data
		std::vector<Vertex>			mVertices;
		std::vector<unsigned int>	mIndices;
		std::vector<Texture>		mTextures;

		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
		void draw(Shader& shader, bool drawElements);
	private:
		//  render data
		unsigned int mVAO, mVBO, mEBO;

		void setupMesh();
};


/*
	VAO = Vertex Array Object
		Raggruppa la configurazione dei vertex attributes e i buffer bindings
		Si genera con glGenVertexArrays, si binda con glBindVertexArray e si elimina con glDeleteVertexArrays

	VBO = Vertex Buffer Object
		Un buffer nella GPU che mantiene i vertex data che verranno usati dal vertex shader
		Si binda con glBindBuffer, poi si usa glBufferData per mandare i dati alla GPU e si elimina con glDeleteBuffers

	EBO = Element Buffer Object
		Usato per mantenere gli indici che referenziaano i vertici in un VBO.

		Si genera con glGenBuffers, si binda con glBindBuffer e si eleimina con glDeleteBuffers
*/