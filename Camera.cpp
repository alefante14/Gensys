#include "Camera.h"

Camera::Camera(
	Window& window,
	glm::vec3 Position, glm::vec3 Front, glm::vec3 Up, glm::vec3 direction,
	float yaw, float pitch,
	float speed, float mouseSensitivity, float fov) 
	:
	mLinkedWindow(window),
	mPosition(Position), mFront(Front), mUp(Up), mDirection(direction),
	mYaw(yaw), mPitch(pitch), 
	mSpeed(speed), mMouseSensitivity(mouseSensitivity), mFov(fov)
{
	//constructor does nothing for now
}

void Camera::processKeyboardInput(Camera_Movement movement, double deltaTime)
{
	float fDeltaTime{ static_cast<float>(deltaTime) };
	
	switch (movement)
	{
	case FORWARD:
		mPosition += mSpeed * fDeltaTime * mDirection;
		break;				  
	case BACKWARD:			  
		mPosition -= mSpeed * fDeltaTime * mDirection;
		break;				  
	case LEFT:				  
		mPosition += mSpeed * fDeltaTime * glm::normalize(glm::cross(mUp, mDirection));
		break;				  
	case RIGHT:				  
		mPosition -= mSpeed * fDeltaTime * glm::normalize(glm::cross(mUp, mDirection));
		break;				  
	case UP:				  
		mPosition += mSpeed * fDeltaTime * mUp;
		break;				  
	case DOWN:				  
		mPosition -= mSpeed * fDeltaTime * mUp;
		break;
	default:
		break;
	}
}

void Camera::processMouseMovementInput(GLFWwindow* window, double xpos, double ypos)
{
	if (mFirstMouse)
	{
		mLastMouseX = xpos;
		mLastMouseY = ypos;
		mFirstMouse = false;
	}

	double xOffset = xpos - mLastMouseX;
	double yOffset = mLastMouseY - ypos;
	mLastMouseX = xpos;
	mLastMouseY = ypos;

	xOffset *= mMouseSensitivity;
	yOffset *= mMouseSensitivity;

	AddYawn(xOffset);
	AddPitch(yOffset);
}

void Camera::processMouseScrollInput(GLFWwindow* window, double xoffset, double yoffset)
{
	mFov -= (float)yoffset;
	if (mFov < MIN_FOV)
		mFov = MIN_FOV;
	if (mFov > MAX_FOV)
		mFov = MAX_FOV;


}



void Camera::pointCameraToTarget(const glm::vec3& pTarget)
{
	mDirection =  - glm::normalize(mPosition - pTarget);
}


void Camera::AddYawn(double yawnInDegrees)
{
	mYaw += yawnInDegrees;
}

void Camera::AddPitch(double pitchInDegrees)
{
	mPitch += pitchInDegrees;
	if (mPitch > 89.0f)
		mPitch = 89.0f;
	if (mPitch < -89.0f)
		mPitch = -89.0f;
}



glm::mat4 Camera::getViewMatrix()
{
	mDirection.x = static_cast<float>(cos(glm::radians(mYaw)) * cos(glm::radians(mPitch)));
	mDirection.y = static_cast<float>(sin(glm::radians(mPitch)));
	mDirection.z = static_cast<float>(sin(glm::radians(mYaw)) * cos(glm::radians(mPitch)));

	mFront = glm::normalize(mDirection);
	
	glm::mat4 returnMatrix = glm::lookAt(mPosition,mPosition + mFront, mUp);
	return returnMatrix;
}

glm::mat4 Camera::getProjectionMatrix()
{
	return glm::perspective(glm::radians(mFov), static_cast<float>(mLinkedWindow.getWidth()) / static_cast<float>(mLinkedWindow.getHeight()), 0.1f, 100.0f);
}

//NOT WORKING
glm::mat4 Camera::getOrthoProjectionMatrix()
{
	return glm::ortho(0.0f, static_cast<float>(mLinkedWindow.getWidth()), 0.0f, static_cast<float>(mLinkedWindow.getHeight()), 0.1f, 100.0f);
}
