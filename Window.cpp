#include "Window.h"



void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Window::Window(const char* title, int width, int height) : SCR_WIDTH(width), SCR_HEIGHT(height)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	mainWindow = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL", NULL, NULL);
	if (mainWindow == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(mainWindow);
	glfwSetFramebufferSizeCallback(mainWindow, Window::framebuffer_size_callback);

	//FINIRE CONSTRUCTOR QUI
}

void Window::swapBuffer()
{
	glfwSwapBuffers(mainWindow);
}

void Window::CloseWindow()
{
	glfwSetWindowShouldClose(mainWindow, true);
}

