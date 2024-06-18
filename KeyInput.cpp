#include "KeyInput.h"

std::vector<KeyInput*> KeyInput::mInstances;

void KeyInput::setupKeyInputs(GLFWwindow* window) {
    glfwSetKeyCallback(window, KeyInput::callback);
}

void KeyInput::callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Send key event to all KeyInput instances
    for (KeyInput* keyInput : mInstances) {
        keyInput->setKeyState(key, action);
    }
}

KeyInput::KeyInput(std::vector<int> keysToMonitor){
    for (int key : keysToMonitor) {
        mKeys[key] = false;
    }
    // Add this instance to the list of instances
    KeyInput::mInstances.push_back(this);
}

KeyInput::~KeyInput() {
    // Remove this instance from the list of instances
    mInstances.erase(std::remove(mInstances.begin(), mInstances.end(), this), mInstances.end());
}

int KeyInput::getKeyState(int key) {
    int result = GLFW_FALSE;
    std::map<int, int>::iterator it = mKeys.find(key);
    if (it != mKeys.end()) {
        result = mKeys[key];
    }
    return result;
}

bool KeyInput::isKeyDown(int key)
{
    int result = GLFW_FALSE;
    std::map<int, int>::iterator it = mKeys.find(key);
    if (it != mKeys.end()) {
        result = mKeys[key];
    }
    if (result == GLFW_PRESS || result || GLFW_RELEASE)
        return true;
    else
        return false;
}



void KeyInput::setKeyState(int key, int currentAction) {
    std::map<int, int>::iterator it = mKeys.find(key);
    if (it != mKeys.end()) {
        mKeys[key] = currentAction;
    }
}

