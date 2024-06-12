#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

//Do we make it external? (look up for Singleton pattern)



class Window{
public:

	static Window& getInstance(unsigned int width = 800, unsigned int height = 600, const std::string& title = "OpenGL Renderer");

	void closeWindow() const;



	void swapBuffer() const;
	int getWidth() const { return SCR_WIDTH; }
	int getHeight() const { return SCR_HEIGHT; }
	GLFWwindow* getWindow() const { return mWindow; }


private:
	Window(unsigned int width, unsigned int height, const std::string& title);
	~Window();

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	bool init();
	
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);




	GLFWwindow* mWindow;

	const unsigned int SCR_WIDTH;
	const unsigned int SCR_HEIGHT;
	std::string mTitle;


};

