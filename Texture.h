#pragma once
#include "CommonHeaders.h"
#include <glad/glad.h>

#include <string>
#include <iostream>

#include "stb_image.h"


class Texture
{
private:
	static unsigned int currentTextureID;
public:
	Texture(const std::string& textureLocation);
};

