#define GLM_ENABLE_EXPERIMENTAL
#include "Shader.h"

Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader)
{
	shaderID = create(vertexShader, fragmentShader);
}

ShaderProgramSource Shader::parse(const std::string& filepath)
{
	std::ifstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)  //if we find the line with #shader
		{
			if (line.find("vertex") != std::string::npos)
				//set mode to vertex
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
				//set mode to fragment
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << '\n';  //insert line in proper stream based on type
		}
	}

	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::compile(unsigned int type, const std::string& source)
{
	unsigned int id;
	id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, NULL);
	glCompileShader(id);

	//logging CompileShader status
	int  success;

	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* infoLog = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, infoLog);
		if (type == GL_VERTEX_SHADER)
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		else if (type == GL_FRAGMENT_SHADER)
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		else
			std::cout << "ERROR::SHADER::UNKNOWN::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return id;
}

unsigned int Shader::GetID()
{
	return shaderID;
}

void Shader::use()
{
	glUseProgram(GetID());  //updating uniform requires to first use the program

}

void Shader::setUniformVec3(const char* name, float x, float y, float z)
{
	unsigned int vectorID = glGetUniformLocation(GetID(), name);
	glUniform3f(vectorID, x, y, z);
}

void Shader::setUniformMatrix4(const char* name, glm::mat4 matrix)
{
	unsigned int matrixID = glGetUniformLocation(GetID(), name);
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, glm::value_ptr(matrix));

}


//Privates

unsigned int Shader::create(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = compile(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = compile(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	//Link Log
	int success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::LINK::LINK_FAILED\n" << infoLog << std::endl;
	}

	//we don't need shader after we linked them
	glDeleteProgram(vs);
	glDeleteProgram(fs);

	return program;
}
