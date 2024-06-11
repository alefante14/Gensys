#include "Texture.h"


Texture::Texture(const std::string& textureLocation)
{
	int width, height, nrChannels;
	unsigned char* data = stbi_load(textureLocation.c_str(), &width, &height, &nrChannels, 0);


	unsigned int texture;
	glGenTextures(1, &texture);  //1: how many textures we want to generate 2: the array where we store them (in our case just a single element)
	glBindTexture(GL_TEXTURE_2D, texture);


	// set the texture wrapping/filtering options (on the currently bound texture object)
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	if (data)
	{
		//check if jpg or png
		if (textureLocation.substr(textureLocation.find_last_of(".") + 1) == "png")
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);  //This will automatically generate all the required mipmaps for the currently bound texture
	}
	else
	{
		std::cout << " Failed to load Texture\n";
	}
	stbi_image_free(data);  //free image memory

	//return texture;
}