#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <glad/glad.h>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	unsigned int shaderID;

	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);


public:
	Shader(const std::string& vertexShader, const std::string& fragmentShader);

	static ShaderProgramSource ParseShader(const std::string& filepath);

	static unsigned int CompileShader(unsigned int type, const std::string& source);

	unsigned int GetID();


};