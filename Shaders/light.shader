#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos,1.0);
}

#shader fragment
#version 330 core

out vec4 FragColor;

void main()
{
	//flip up image exercise
	//FragColor = mix(texture(ourTexture1, TexCoord), texture(ourTexture2 , TexCoord * vec2(1.0, -1.0)), 0.5);
	FragColor = vec4( 1.0);
}