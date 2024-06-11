#pragma once
#include <GLFW/glfw3.h>

#include <map>
#include <vector>

class KeyInput {
public:
    //We have to call this every frame to update key events in current frame, calls callback
    static void setupKeyInputs(GLFWwindow* window);


private:
    // The GLFW callback for key events.  Sends events to all KeyInput instances
    static void callback(GLFWwindow* window, int key, int scancode, int action, int mods);
   
    // Keep a list of all KeyInput instances and notify them all of key events
    static std::vector<KeyInput*> instances;


public:
    // Takes a list of which keys to keep state for
    KeyInput(std::vector<int> keysToMonitor);
    ~KeyInput();
    // If this KeyInput is enabled and the given key is monitored,
    // returns pressed state.  Else returns false.
    int getKeyState(int key);

    //get simpler key state that is true only if the key is pressed
    bool isKeyDown(int key);



private:
    // Used internally to update key states.  Called by the GLFW callback.
    void setKeyState(int key, int currentAction);
    // Map from monitored keyes to their pressed states
    std::map<int, int> keys;




};




