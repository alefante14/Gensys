#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

//Do we make it external? (look up for Singleton pattern)
class Window
{
private:


	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

public:
	const unsigned int SCR_WIDTH;
	const unsigned int SCR_HEIGHT;
	GLFWwindow* mainWindow;

	Window(const char* title, int width, int height);

	void swapBuffer();

	void CloseWindow();
};

