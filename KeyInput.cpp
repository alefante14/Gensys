#include "KeyInput.h"

std::vector<KeyInput*> KeyInput::instances;

void KeyInput::setupKeyInputs(GLFWwindow* window) {
    glfwSetKeyCallback(window, KeyInput::callback);
}

void KeyInput::callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Send key event to all KeyInput instances
    for (KeyInput* keyInput : instances) {
        keyInput->setKeyState(key, action);
    }
}

KeyInput::KeyInput(std::vector<int> keysToMonitor){
    for (int key : keysToMonitor) {
        keys[key] = false;
    }
    // Add this instance to the list of instances
    KeyInput::instances.push_back(this);
}

KeyInput::~KeyInput() {
    // Remove this instance from the list of instances
    instances.erase(std::remove(instances.begin(), instances.end(), this), instances.end());
}

int KeyInput::getKeyState(int key) {
    int result = GLFW_FALSE;
    std::map<int, int>::iterator it = keys.find(key);
    if (it != keys.end()) {
        result = keys[key];
    }
    return result;
}

bool KeyInput::isKeyDown(int key)
{
    int result = GLFW_FALSE;
    std::map<int, int>::iterator it = keys.find(key);
    if (it != keys.end()) {
        result = keys[key];
    }
    if (result == GLFW_PRESS || result || GLFW_RELEASE)
        return true;
    else
        return false;
}



void KeyInput::setKeyState(int key, int currentAction) {
    std::map<int, int>::iterator it = keys.find(key);
    if (it != keys.end()) {
        keys[key] = currentAction;
    }
}

