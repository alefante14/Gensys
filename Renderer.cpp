#include "Renderer.h"



void processInput(KeyInput& keyInput, Window& window, Camera& cam);

static unsigned int CreateTexture(const std::string& textureLocation);

namespace global
{
	//zero initialization
	double g_deltaTime{};
	double g_lastFrame{};
}


Renderer::Renderer() :
	mainKeyInput{ {GLFW_KEY_ESCAPE, GLFW_KEY_RIGHT, GLFW_KEY_LEFT, GLFW_KEY_DOWN, GLFW_KEY_UP, GLFW_KEY_F, GLFW_KEY_A, GLFW_KEY_S, GLFW_KEY_D, GLFW_KEY_W, GLFW_KEY_SPACE, GLFW_KEY_C } },
	mainCamera{ windowHandler }
{
	


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw std::runtime_error("Failed to initialize GLAD");
	}

	//taking and compiling shaders
	ShaderProgramSource textureSource = Shader::parse("Shaders/Texture.shader");
	loadedShaders["texture"] =  Shader(textureSource.VertexSource, textureSource.FragmentSource);

	ShaderProgramSource lightReflectSource = Shader::parse("Shaders/lightReflect.shader");
	loadedShaders["lightReflect"] = Shader(lightReflectSource.VertexSource, lightReflectSource.FragmentSource);


	ShaderProgramSource lightSource = Shader::parse("Shaders/light.shader");
	loadedShaders["light"] = Shader(lightSource.VertexSource, lightSource.FragmentSource);


	ShaderProgramSource basicSource = Shader::parse("Shaders/basic.shader");
	loadedShaders["basic"] = Shader(basicSource.VertexSource, basicSource.FragmentSource);


	std::vector<Vertex> pyramidVertices = {
		// Positions								Normals						Texture coord            Colors
		// Base
		Vertex{ glm::vec3(- 0.5f,  0.0f, -0.5f), glm::vec3(), glm::vec2(0.0f,0.0f), glm::vec3(1.0f, 1.0f, 0.0f) },
		Vertex{ glm::vec3(0.5f,  0.0f, -0.5f), glm::vec3(), glm::vec2(0.0f,0.0f),  glm::vec3(1.0f, 1.0f, 0.0f) },
		Vertex{ glm::vec3(0.5f,  0.0f,  0.5f), glm::vec3(), glm::vec2(0.0f,0.0f),  glm::vec3(1.0f, 1.0f, 0.0f) },
		Vertex{ glm::vec3(-0.5f,  0.0f,  0.5f), glm::vec3(), glm::vec2(0.0f,0.0f), glm::vec3(1.0f, 1.0f, 0.0f) },
		Vertex{ glm::vec3(0.0f,  0.8f,  0.0f), glm::vec3(), glm::vec2(0.0f,0.0f),  glm::vec3(0.0f, 1.0f, 0.0f) }


	};

	std::vector<unsigned int> pyramidIndices = {
		// Base face (quadrilateral)
		0, 1, 2,   // Triangle 1 of the base (1-2-3)
		0, 2, 3,   // Triangle 2 of the base (1-3-4)

		// Side faces (triangles)
		0, 1, 4,   // Face 1 (1-2-5)
		1, 2, 4,   // Face 2 (2-3-5)
		2, 3, 4,   // Face 3 (3-4-5)
		3, 0, 4    // Face 4 (4-1-5)
	};

	std::vector<Texture> tex;
	Mesh pyramid{ pyramidVertices, pyramidIndices, tex };
	loadedMeshes["pyramid"] = pyramid;


	std::vector<Vertex> cubeVertices = {
		// Positions								Normals						Texture coord            Colors
		// front face
		Vertex{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.0f,  0.0f,  1.0f),	glm::vec2(),				glm::vec3(1.0f, 0.0f, 0.0f) },
		Vertex{ glm::vec3(0.5f, -0.5f,  0.5f),	glm::vec3(0.0f,  0.0f,  1.0f), glm::vec2(0.0f,0.0f),		glm::vec3(1.0f, 0.0f, 0.0f) },
		Vertex{ glm::vec3(0.5f,  0.5f,  0.5f),	glm::vec3(0.0f,  0.0f,  1.0f), glm::vec2(0.0f,0.0f),		glm::vec3(1.0f, 0.0f, 0.0f) },
		Vertex{ glm::vec3(-0.5f,  0.5f,  0.5f),	glm::vec3(0.0f,  0.0f,  1.0f), glm::vec2(0.0f,0.0f),	glm::vec3(1.0f, 0.0f, 0.0f) },
		//back face
		Vertex{ glm::vec3(-0.5f,  -0.5f,  -0.5f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec2(0.0f,0.0f),	glm::vec3(1.0f, 1.0f, 0.0f) },
		Vertex{ glm::vec3(0.5f,  -0.5f,  -0.5f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec2(0.0f,0.0f),	glm::vec3(1.0f, 1.0f, 0.0f) },
		Vertex{ glm::vec3(0.5f,  0.5f,  -0.5f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec2(0.0f,0.0f),	glm::vec3(1.0f, 1.0f, 0.0f) },
		Vertex{ glm::vec3(-0.5f,  0.5f,  -0.5f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec2(0.0f,0.0f),	glm::vec3(1.0f, 1.0f, 0.0f) },
		//left face
		Vertex{ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0.0f,0.0f),	glm::vec3(1.0f,  0.0f,  0.0f) },
		Vertex{ glm::vec3(-0.5f,  0.5f,  -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0.0f,0.0f),  glm::vec3(1.0f,  0.0f,  0.0f) },
		Vertex{ glm::vec3(-0.5f,  -0.5f,  -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0.0f,0.0f), glm::vec3(1.0f,  0.0f,  0.0f) },
		Vertex{ glm::vec3(-0.5f,  -0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0.0f,0.0f),  glm::vec3(1.0f,  0.0f,  0.0f) },
		//right face
		Vertex{ glm::vec3(0.5f,  0.5f,  0.5f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec2(0.0f,0.0f),		glm::vec3(1.0f,  0.0f,  0.0f) },
		Vertex{ glm::vec3(0.5f,  0.5f,  -0.5f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec2(0.0f,0.0f),	glm::vec3(1.0f,  0.0f,  0.0f) },
		Vertex{ glm::vec3(0.5f,  -0.5f,  -0.5f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec2(0.0f,0.0f),	glm::vec3(1.0f,  0.0f,  0.0f) },
		Vertex{ glm::vec3(0.5f,  -0.5f,  0.5f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec2(0.0f,0.0f),	glm::vec3(1.0f,  0.0f,  0.0f) },
		//bottom face
		Vertex{ glm::vec3(-0.5f,  -0.5f,  -0.5f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec2(0.0f,0.0f),  glm::vec3(0.0f,  1.0f,  0.0f) },
		Vertex{ glm::vec3(0.5f,  -0.5f,  -0.5f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec2(0.0f,0.0f),	glm::vec3(0.0f,  1.0f,  0.0f) },
		Vertex{ glm::vec3(0.5f,  -0.5f,  0.5f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec2(0.0f,0.0f),	glm::vec3(0.0f,  1.0f,  0.0f) },
		Vertex{ glm::vec3(-0.5f,  -0.5f,  0.5f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec2(0.0f,0.0f),	glm::vec3(0.0f,  1.0f,  0.0f) },
		//top face
		Vertex{ glm::vec3(-0.5f,  0.5f,  -0.5f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec2(0.0f,0.0f),	glm::vec3(0.0f,  1.0f,  0.0f) },
		Vertex{ glm::vec3(0.5f,  0.5f,  -0.5f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec2(0.0f,0.0f),	glm::vec3(0.0f,  1.0f,  0.0f) },
		Vertex{ glm::vec3(0.5f,  0.5f,  0.5f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec2(0.0f,0.0f),		glm::vec3(0.0f,  1.0f,  0.0f) },
		Vertex{ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec2(0.0f,0.0f),	glm::vec3(0.0f,  1.0f,  0.0f) }
	};

	std::vector<unsigned int> cubeIndices = {
		// front face
		0, 1, 2, 2, 3, 0,
		// back face
		4, 5, 6, 6, 7, 4,
		// left face
		8, 9, 10, 10, 11, 8,
		// right face
		12, 13, 14, 14, 15, 12,
		// bottom face
		16, 17, 18, 18, 19, 16,
		// top face
		20, 21, 22, 22, 23, 20
	};


	Mesh cube{ cubeVertices, cubeIndices, tex };
	loadedMeshes["cube"] = cube;


	//view matrix to move the camera
	mainCamera.pointCameraToTarget(glm::vec3(0.0f, 0.0f, 0.0f));

	//MOUSE
	glfwSetInputMode(windowHandler.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	init();
}

Renderer ::~Renderer ()
{
}




void Renderer::init()
{


	// render loop
	while (!glfwWindowShouldClose(windowHandler.getWindow()))
	{
		//TIME

		double currentFrame = glfwGetTime();
		global::g_deltaTime = currentFrame - global::g_lastFrame;
		global::g_lastFrame = currentFrame;



		// input
		// -----
		mainKeyInput.setupKeyInputs(windowHandler.getWindow());
		processInput(mainKeyInput, windowHandler, mainCamera);

		glfwSetWindowUserPointer(windowHandler.getWindow(), &mainCamera);

		//MOUSE
		glfwSetCursorPosCallback(windowHandler.getWindow(), [](GLFWwindow* window, double x, double y) //lamba function implementation
			{
				if (Camera* cam = static_cast<Camera*>(glfwGetWindowUserPointer(window)))
					cam->processMouseMovementInput(window, x, y);
			});
		glfwSetScrollCallback(windowHandler.getWindow(), [](GLFWwindow* window, double x, double y)
			{
				if (Camera* cam = static_cast<Camera*>(glfwGetWindowUserPointer(window)))
					cam->processMouseScrollInput(window, x, y);
			});


		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //we are using a depth buffer, we need to clear it before next iteration


		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

	

		//Draw basic pyramid
		loadedShaders["basic"].use();

		loadedShaders["basic"].setUniformMatrix4("view", mainCamera.getViewMatrix());
		loadedShaders["basic"].setUniformMatrix4("projection", mainCamera.getProjectionMatrix());

		//Draw pyramids
		for (unsigned int i = 0; i < pyramidPositions.size(); i++)
		{
			glm::mat4 pyramidModel = glm::mat4(1.0f);
			pyramidModel = glm::translate(pyramidModel, pyramidPositions[i]);
			pyramidModel = glm::rotate(pyramidModel, (float)glfwGetTime() * glm::radians(20.0f), glm::vec3(0.0f, 1.0f, 0.0f));  //rotating on X-Axis
			loadedShaders["basic"].setUniformMatrix4("model", pyramidModel);
		
			loadedMeshes["pyramid"].draw(loadedShaders["basic"]);
		}

		//Draw light cubes
		loadedShaders["light"].use();

		loadedShaders["light"].setUniformMatrix4("view", mainCamera.getViewMatrix());
		loadedShaders["light"].setUniformMatrix4("projection", mainCamera.getProjectionMatrix());
		for (unsigned int i = 0; i < lightCubePositions.size(); i++)
		{
			glm::mat4 lightCubeModel = glm::mat4(1.0f);
			lightCubeModel = glm::translate(lightCubeModel, lightCubePositions[i]);
			lightCubeModel = glm::scale(lightCubeModel, glm::vec3(0.2f));
			loadedShaders["light"].setUniformMatrix4("model", lightCubeModel);

			loadedMeshes["cube"].draw(loadedShaders["light"]);
		}

		//Draw light reflect cubes
		loadedShaders["lightReflect"].use();

		loadedShaders["lightReflect"].setUniformVec3("lightColor", 1.0f, 1.0f, 1.0f);
		loadedShaders["lightReflect"].setUniformVec3("lightPos", lightCubePositions[0]);  //same pos as light cube
		loadedShaders["lightReflect"].setUniformVec3("viewPos", mainCamera.getPosition());

		loadedShaders["lightReflect"].setUniformMatrix4("view", mainCamera.getViewMatrix());
		loadedShaders["lightReflect"].setUniformMatrix4("projection", mainCamera.getProjectionMatrix());
		for (unsigned int i = 0; i < reflectLightCubePositions.size(); i++)
		{
			glm::mat4 cubeModel = glm::mat4(1.0f);
			cubeModel = glm::translate(cubeModel, reflectLightCubePositions[i]);
			cubeModel = glm::rotate(cubeModel, (float)glfwGetTime() * glm::radians(20.0f), glm::vec3(0.0f, 1.0f, 0.0f));  //rotating on X-Axis
			loadedShaders["lightReflect"].setUniformMatrix4("model", cubeModel);

			loadedMeshes["cube"].draw(loadedShaders["lightReflect"]);
		}

		glBindVertexArray(0);


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		windowHandler.swapBuffer();
		glfwPollEvents();
	}


	glfwTerminate();

}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(KeyInput& keyInput, Window& window, Camera& cam)
{

	if (keyInput.getKeyState(GLFW_KEY_ESCAPE) == GLFW_PRESS)
		window.closeWindow();
	

	if (keyInput.getKeyState(GLFW_KEY_F) == GLFW_REPEAT)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else if (keyInput.getKeyState(GLFW_KEY_F) == 0)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	if ((keyInput.isKeyDown(GLFW_KEY_RIGHT)) || (keyInput.isKeyDown(GLFW_KEY_D)))
	{
		cam.processKeyboardInput(RIGHT,global::g_deltaTime);
	}
	else if ((keyInput.isKeyDown(GLFW_KEY_LEFT)) || (keyInput.isKeyDown(GLFW_KEY_A)))
	{
		cam.processKeyboardInput(LEFT, global::g_deltaTime);
	}

	if ((keyInput.isKeyDown(GLFW_KEY_UP)|| (keyInput.isKeyDown(GLFW_KEY_W))))
	{
		cam.processKeyboardInput(FORWARD, global::g_deltaTime);
	}
	else if ((keyInput.isKeyDown(GLFW_KEY_DOWN)) || (keyInput.isKeyDown(GLFW_KEY_S)))
	{
		cam.processKeyboardInput(BACKWARD, global::g_deltaTime);
	}

	if ((keyInput.isKeyDown(GLFW_KEY_SPACE)))
	{
		cam.processKeyboardInput(UP, global::g_deltaTime);
	}
	else if ((keyInput.isKeyDown(GLFW_KEY_C)))
	{
		cam.processKeyboardInput(DOWN, global::g_deltaTime);
	}
}




unsigned int CreateTexture(const std::string& textureLocation)
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

	return texture;
}





