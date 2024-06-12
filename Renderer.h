#pragma once
#include <glad/glad.h>

#include "KeyInput.h"
#include "Shader.h"
#include "Window.h"
#include "Camera.h"

#include "stb_image.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

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
