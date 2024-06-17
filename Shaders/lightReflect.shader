#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 3) in vec3 aColor;



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
	vertexNormal = mat3(transpose(inverse(model))) * aNormal;  //better calculate inverse on the CPU
	fragPos = vec3(model * vec4(aPos, 1.0));
}

#shader fragment
#version 330 core

in vec3 vertexColor;
in vec3 vertexNormal;
in vec3 fragPos;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;


out vec4 FragColor;

void main()
{
	float specularStrength = 0.5;

	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;
	
	//normal vector and light direction
	vec3 norm = normalize(vertexNormal);
	vec3 lightDir = normalize(lightPos - fragPos);

	//diffuse light through normal
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	//specular lighting
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect( - lightDir, norm);  //lightDir is negative cause reflect function expects first vector to point FROM light
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);  //32 is the shininess value
	vec3 specular = specularStrength * spec * lightColor;

	vec3 result = (ambient + diffuse + specular) * vertexColor;

	FragColor = vec4(result, 1.0);
}