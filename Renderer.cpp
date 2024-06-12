#define STB_IMAGE_IMPLEMENTATION
#define GLM_ENABLE_EXPERIMENTAL

#include "Renderer.h"


Renderer ::Renderer ()
{
}

Renderer ::~Renderer ()
{
}

void Renderer::init()
{

}


void mouseMovementCallback(GLFWwindow* window, double xpos, double ypos);
void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);


void processInput(KeyInput& keyInput, Window& window);




static unsigned int CreateTexture(const std::string& textureLocation);



Window& windowHandler = Window::getInstance(SCR_WIDTH, SCR_HEIGHT, "NEW OPENGL IMP");

Camera mainCamera{windowHandler};

KeyInput mainKeyInput = KeyInput({ GLFW_KEY_ESCAPE, GLFW_KEY_RIGHT, GLFW_KEY_LEFT, GLFW_KEY_DOWN, GLFW_KEY_UP, GLFW_KEY_F, GLFW_KEY_A, GLFW_KEY_S, GLFW_KEY_D, GLFW_KEY_W, GLFW_KEY_SPACE, GLFW_KEY_C });


//DELTA TIME
double deltaTime = 0.0f;
double lastFrame = 0.0f;

int main()
{

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//taking and compiling shaders
	ShaderProgramSource source = Shader::ParseShader("Shaders/Basic.shader");
	Shader shaderProgram = Shader(source.VertexSource, source.FragmentSource);

	//cube
	float positions[] = {
		//positions				colors			texCoord
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f
	};

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	//Indices MUST be unsigned 
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 2,   // first triangle
		2, 0, 3    // second triangle
	};


	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) Objects, and then configure vertex attributes(s).
	/*
		// create object
		unsigned int objectId = 0;
		glGenObject(1, &objectId);
		// bind/assign object to context
		glBindObject(GL_WINDOW_TARGET, objectId);
		// set options of object currently bound to GL_WINDOW_TARGET
		glSetObjectOption(GL_WINDOW_TARGET, GL_OPTION_WINDOW_WIDTH,  800);
		glSetObjectOption(GL_WINDOW_TARGET, GL_OPTION_WINDOW_HEIGHT, 600);
		// set context target back to default
		glBindObject(GL_WINDOW_TARGET, 0);
	
	****************************************************************************************************************************************************************************

	VAO = Vertex Array Object
		Raggruppa la configurazione dei vertex attributes e i buffer bindings
		Si genera con glGenVertexArrays, si binda con glBindVertexArray e si elimina con glDeleteVertexArrays

	VBO = Vertex Buffer Object
		Un buffer nella GPU che mantiene i vertex data che verranno usati dal vertex shader
		Si binda con glBindBuffer, poi si usa glBufferData per mandare i dati alla GPU e si elimina con glDeleteBuffers

	EBO = Element Buffer Object
		Usato per mantenere gli indici che referenziaano i vertici in un VBO.

		Si genera con glGenBuffers, si binda con glBindBuffer e si eleimina con glDeleteBuffers

	*/


	unsigned int  VAO; //Vertex Array Object
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);



	unsigned int VBO;  //Vertex Buffer Object
	glGenBuffers(1, &VBO);  //Generate Buffer with ID=1
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//Bind buffer with proper type
	/*
	GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
	GL_STATIC_DRAW: the data is set only once and used many times.
	GL_DYNAMIC_DRAW: the data is changed a lot and used many times.
	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);  //copy data into buffer
	//We are describing the layout of our vertex attributes
	//Positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//Colors
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//Texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	unsigned int EBO;  //Element Buffer Object
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	stbi_set_flip_vertically_on_load(true);  //to flip up every import
	unsigned int containerTexture = CreateTexture("Textures/wall.jpg");
	unsigned int faceTexture = CreateTexture("Textures/bird.png");


	glUseProgram(shaderProgram.GetID()); // don't forget to activate the shader before setting uniforms!  
	glUniform1i(glGetUniformLocation(shaderProgram.GetID(), "ourTexture1"), 0); //set it manually
	glUniform1i(glGetUniformLocation(shaderProgram.GetID(), "ourTexture2"), 1);


	//view matrix to move the camera
	mainCamera.pointCameraToTarget(glm::vec3(0.0f, 0.0f, 0.0f));

	//MOUSE
	glfwSetInputMode(windowHandler.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);



	// render loop
	while (!glfwWindowShouldClose(windowHandler.getWindow()))
	{
		//TIME
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;


		// input
		// -----
		mainKeyInput.setupKeyInputs(windowHandler.getWindow());
		processInput(mainKeyInput, windowHandler);

		//MOUSE
		glfwSetCursorPosCallback(windowHandler.getWindow(), mouseMovementCallback);
		glfwSetScrollCallback(windowHandler.getWindow(), mouseScrollCallback);



		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //we are using a depth buffer, we need to clear it before next iteration




		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);  //activate the texture unit first before binding texture
		glBindTexture(GL_TEXTURE_2D, containerTexture);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, faceTexture);


		glUseProgram(shaderProgram.GetID());  //updating uniform requires to first use the program


		// note that we're translating the scene in the reverse direction of where we want to move

		

		unsigned int modelMatrix = glGetUniformLocation(shaderProgram.GetID(), "model");
		unsigned int viewMatrix = glGetUniformLocation(shaderProgram.GetID(), "view");
		unsigned int projectionMatrix = glGetUniformLocation(shaderProgram.GetID(), "projection");


		//glm::mat4 view = mainCamera.getViewMatrix();

		glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(mainCamera.getViewMatrix()));
		glUniformMatrix4fv(projectionMatrix, 1, GL_FALSE, glm::value_ptr(mainCamera.getProjectionMatrix()));
		//glUniformMatrix4fv(projectionMatrix, 1, GL_FALSE, glm::value_ptr(mainCamera.getOrthoProjectionMatrix()));

		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(20.0f * (i + 1)), glm::vec3(0.5f, 1.0f, 0.0f));  //rotating on X-Axis
			glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
		/*
		* The glDrawElements function takes its indices from the EBO currently bound to the GL_ELEMENT_ARRAY_BUFFER target.
		* This means we have to bind the corresponding EBO each time we want to render an object with indices which again is a bit cumbersome.
		*/
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,VBO);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		windowHandler.swapBuffer();
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;


}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(KeyInput& keyInput, Window& window)
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
		mainCamera.processKeyboardInput(RIGHT,deltaTime);
	}
	else if ((keyInput.isKeyDown(GLFW_KEY_LEFT)) || (keyInput.isKeyDown(GLFW_KEY_A)))
	{
		mainCamera.processKeyboardInput(LEFT, deltaTime);
	}

	if ((keyInput.isKeyDown(GLFW_KEY_UP)|| (keyInput.isKeyDown(GLFW_KEY_W))))
	{
		mainCamera.processKeyboardInput(FORWARD, deltaTime);
	}
	else if ((keyInput.isKeyDown(GLFW_KEY_DOWN)) || (keyInput.isKeyDown(GLFW_KEY_S)))
	{
		mainCamera.processKeyboardInput(BACKWARD, deltaTime);
	}

	if ((keyInput.isKeyDown(GLFW_KEY_SPACE)))
	{
		mainCamera.processKeyboardInput(UP, deltaTime);
	}
	else if ((keyInput.isKeyDown(GLFW_KEY_C)))
	{
		mainCamera.processKeyboardInput(DOWN, deltaTime);
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

void mouseMovementCallback(GLFWwindow* window, double xpos, double ypos)
{
	mainCamera.processMouseMovementInput(window, xpos, ypos);


}

void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	mainCamera.processMouseScrollInput(window, xoffset, yoffset);


}



