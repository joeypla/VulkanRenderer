#pragma once

#include <GLFW/glfw3.h>
#include <functional>
#include <map>

/* I don't want to have GLFW input jibble jabble used elsewhere, so we have our own. They still just map to GLFW. */
enum KeyInput{
	ESC = GLFW_KEY_ESCAPE,
	K = GLFW_KEY_K
};

struct InputDelegate
{
	void* pObject;
	std::function<void()> func;
};

typedef void voidFunc(void);
typedef std::vector<voidFunc*> voidFuncList;

/* Abstract base class for anything that needs to listen to input events */
class InputListener
{
	virtual void KeyPressed(KeyInput key) = 0;
	virtual void KeyReleased(KeyInput key) = 0;
};

class InputManager
{
public:
	/* The class requires the window to poll input on. */
	InputManager(GLFWwindow* window);

	/* polls for events, and fires off to subscribed agents if necessary */
	void update();

	void bindFunction(const std::string& action, voidFunc func);
	void clearBindings(voidFunc func);
private:
	GLFWwindow* window;

	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	
	std::map<std::string, voidFuncList> bindMap;


	std::map<std::string, std::vector<KeyInput>> actionMap;
};