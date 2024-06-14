#pragma once
#include <glad/glad.h>

#include "KeyInput.h"
#include "Shader.h"
#include "Window.h"
#include "Camera.h"
#include "Mesh.h"

#include "stb_image.h"




#include "CommonHeaders.h"


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
};
