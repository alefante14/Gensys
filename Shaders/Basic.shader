#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 inColor;
layout (location = 2) in vec2 inTexCoord;
out vec4 vertexColor;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos,1.0);
	vertexColor = vec4(inColor, 1.0); 
	TexCoord = inTexCoord;
}

#shader fragment
#version 330 core

in vec4 vertexColor;
in vec2 TexCoord;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

out vec4 FragColor;



void main()
{
	//flip up image exercise
	//FragColor = mix(texture(ourTexture1, TexCoord), texture(ourTexture2 , TexCoord * vec2(1.0, -1.0)), 0.5);
	FragColor = mix(texture(ourTexture1, TexCoord), texture(ourTexture2 , TexCoord), 0.5);;
}