#include "Window.h"



Window& Window::getInstance(unsigned int width, unsigned int height, const std::string& title)
{
	static Window instance(width, height, title);
	return instance;
}

void Window::closeWindow() const
{
	return glfwSetWindowShouldClose(mWindow, true);
}


Window::Window(unsigned int width, unsigned int height, const std::string& title) : SCR_WIDTH(width), SCR_HEIGHT(height), mTitle(title), mWindow(nullptr)
{
	if (!init())
	{
		std::cerr << "Failed to initialize GLFW window " << std::endl;
	}
}


Window::~Window()
{
	glfwSetWindowShouldClose(mWindow, true);
	if (mWindow) {
		glfwDestroyWindow(mWindow);
		mWindow = nullptr;
	}
	glfwTerminate();
}


bool Window::init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	mWindow = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, mTitle.c_str(), NULL, NULL);
	if (mWindow == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(mWindow);
	glfwSetFramebufferSizeCallback(mWindow, Window::framebuffer_size_callback);

	return true;
}


void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Window::swapBuffer() const
{
	glfwSwapBuffers(mWindow);
}





