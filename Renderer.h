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

public:
	KeyInput mainKeyInput;
	Window& mWindowHandler = Window::getInstance(SCR_WIDTH, SCR_HEIGHT, "Gensys");
	Camera mMainCamera;

private:
	std::map<std::string, Mesh> mLoadedMeshes;
	std::map<std::string, Shader> mLoadedShaders;



	std::vector<glm::vec3> mPyramidPositions{
		glm::vec3(10.0f,  0.0f,  0.0f),
		glm::vec3(6.0f,  0.0f,  0.0f)
	};

	std::vector<glm::vec3> mLightCubePositions{
		glm::vec3(0.0f,  2.0f,  0.0f)
	};

	std::vector<glm::vec3> mReflectLightCubePositions{
		glm::vec3(2.0f,  0.0f,  0.0f),
		glm::vec3(-3.0f,  0.0f,  -3.0f)
	};

};
