#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <glad/glad.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	unsigned int shaderID;

	unsigned int create(const std::string& vertexShader, const std::string& fragmentShader);


public:
	Shader();

	Shader(const std::string& vertexShader, const std::string& fragmentShader);

	static ShaderProgramSource parse(const std::string& filepath);

	static unsigned int compile(unsigned int type, const std::string& source);

	unsigned int GetID();

	void use();

	void setUniformVec3(const char* name, float x, float y, float z);

	void setUniformVec3(const char* name, glm::vec3 vector);

	void setUniformMatrix4(const char* name, glm::mat4 matrix);



};