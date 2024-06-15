#include "Model.h"


void Model::Draw(Shader& shader)
{
	for (unsigned int i = 0; i < mMeshes.size(); i++)
	{
		mMeshes[i].draw(shader, true);  //check this later
	}
}

void Model::loadModel(std::string path)
{
	Assimp::Importer importer;
	/*
	aiProcess_Triangulate transforms every primitive shapes in triangles
	aiProcess_FlipUVsf flip up textures on y-axis when necessary
	
	Other useful options
    aiProcess_GenNormals: creates normal vectors for each vertex if the model doesn't contain normal vectors.
    aiProcess_SplitLargeMeshes: splits large meshes into smaller sub-meshes which is useful if your rendering has a maximum number of vertices allowed and can only process smaller meshes.
    aiProcess_OptimizeMeshes: does the reverse by trying to join several meshes into one larger mesh, reducing drawing calls for optimization.

	*/
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}
	mDirectory = path.substr(0, path.find_last_of('/'));

	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	//process all the node meshes
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		mMeshes.push_back(processMesh(mesh, scene));
	}
	//then the same for each children
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
	//take note of parent-child relationship?
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		vertex.Position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vertex.Normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		if (mesh->mTextureCoords[0])  //does the mesh contain texture coordinates?
			vertex.TexCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		else
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);

	vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	
	//LATER ADD PROCESS MATERIAL

	return Mesh(vertices,indices,textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	return std::vector<Texture>();
}
