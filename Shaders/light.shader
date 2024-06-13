#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 vertexColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos,1.0);
	vertexColor = aColor;
}

#shader fragment
#version 330 core

in vec3 vertexColor;

out vec4 FragColor;

void main()
{
	//flip up image exercise
	//FragColor = mix(texture(ourTexture1, TexCoord), texture(ourTexture2 , TexCoord * vec2(1.0, -1.0)), 0.5);
	FragColor = vec4(vertexColor, 1.0);
}