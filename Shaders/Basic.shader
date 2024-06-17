#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexture;
layout (location = 3) in vec3 inColor;

out vec4 objectColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos,1.0);
	objectColor = vec4(inColor, 1.0); 
}

#shader fragment
#version 330 core

in vec4 objectColor;

out vec4 FragColor;



void main()
{
	FragColor = objectColor;
}