#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
    this->mVertices = vertices;
    this->mIndices = indices;
    this->mTextures = textures;

    setupMesh();
}

void Mesh::draw(Shader& shader)
{
	glBindVertexArray(mVAO);

	//glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(mVertices.size()));
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mIndices.size()), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void Mesh::setupMesh()
{
	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &mVBO);  //Generate Buffer with ID=1
	glGenBuffers(1, &mEBO);

	glBindVertexArray(mVAO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	/*
	GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
	GL_STATIC_DRAW: the data is set only once and used many times.
	GL_DYNAMIC_DRAW: the data is changed a lot and used many times.
	*/
	glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), &mVertices[0], GL_STATIC_DRAW);  //copy data into buffer

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(unsigned int), &mIndices[0], GL_STATIC_DRAW);

	//We are describing the layout of our vertex attributes
	//Positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
	glEnableVertexAttribArray(0);
	//Normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	glEnableVertexAttribArray(1);
	//Texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
	glEnableVertexAttribArray(2);
	//Colors
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Colors));
	glEnableVertexAttribArray(3);



	glBindVertexArray(0);
}
