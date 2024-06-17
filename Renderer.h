#pragma once
#include "CommonHeaders.h"
#include <glad/glad.h>

#include "KeyInput.h"
#include "Shader.h"
#include "Window.h"
#include "Camera.h"
#include "Mesh.h"

#include "stb_image.h"







// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

class Renderer
{
public:
	Renderer();
	~Renderer();

private:
	void init();

	std::vector<Mesh> loadedMeshes;
	std::vector<Shader> loadedShaders;

	std::vector<glm::vec3> pyramidPositions = {
		glm::vec3(10.0f,  0.0f,  0.0f),
		glm::vec3(6.0f,  0.0f,  0.0f)
	};

};
