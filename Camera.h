#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>

#include "Window.h"


enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 10.0f;
const float SENSITIVITY = 0.1f;
const float FOV = 45.0f;

const float MIN_FOV = 1.0f;
const float MAX_FOV = 45.0f;



class Camera
{
private:
	const Window& linkedWindow;

	glm::vec3 mFront;
	glm::vec3 mUp;

	double mYaw;
	double mPitch;
	
	bool firstMouse = true;
	double lastX = static_cast<double>(linkedWindow.SCR_WIDTH) / 2;
	double lastY = static_cast<double>(linkedWindow.SCR_HEIGHT) / 2;


public:
	glm::vec3 mPosition;
	glm::vec3 mDirection;

	float mSpeed;
	float mMouseSensitivity;
	float mFov;

	//Argoument are : (Position, Front, Up, yaw, pitch, speed, mouseSensitivity, zoom)
	Camera(
		const Window& window,
		glm::vec3 Position = glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3 Front = glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3 Direction = glm::vec3(0.0f, 0.0f, 0.0f),
		float yaw = YAW, float pitch = PITCH,
		float speed = SPEED, float mouseSensitivity = SENSITIVITY, float fov = FOV
	);


	void pointCameraToTarget(const glm::vec3& pTarget);

	void processKeyboardInput(Camera_Movement movement, double deltaTime);
	void processMouseMovementInput(GLFWwindow* window, double xpos, double ypos);
	void processMouseScrollInput(GLFWwindow* window, double xoffset, double yoffset);

	void AddYawn(double yawnInDegrees);
	void AddPitch(double pitchInDegrees);

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();

	glm::mat4 getOrthoProjectionMatrix();  //NOT WORKING

};
