#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 3) in vec3 aNormal;

out vec3 vertexColor;
out vec3 vertexNormal;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos,1.0);
	vertexColor = aColor;
	vertexNormal = aNormal;
	fragPos = vec3(model * vec4(aPos, 1.0));
}

#shader fragment
#version 330 core

in vec3 vertexColor;
in vec3 vertexNormal;
in vec3 fragPos;

uniform vec3 lightColor;
uniform vec3 lightPos;

out vec4 FragColor;

void main()
{
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;

	vec3 norm = normalize(vertexNormal);
	vec3 lightDir = normalize(lightPos - fragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 result = (ambient + diffuse) * vertexColor;

	FragColor = vec4(result, 1.0);
}