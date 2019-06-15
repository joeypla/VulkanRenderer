#include "InputManager.h"
#include <algorithm>
#include <iostream>
InputManager::InputManager(GLFWwindow* window)
{
	window = window;

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetWindowUserPointer(window, (void*)this);

	/* 
	C style function callbacks don't work with member functions. This is a workaround since
	glfw allows us to pass in a user-defined user pointer for the window, in this case, this input manager. 
	
	This implementation is a variation on: https://stackoverflow.com/questions/7676971/pointing-to-a-function-that-is-a-class-member-glfw-setkeycallback
	
	*/
	auto func = [](GLFWwindow* w, int key, int scanCode, int action, int mode)
	{
		static_cast<InputManager*>(glfwGetWindowUserPointer(w))->keyCallback(w, key, scanCode, action, mode);
	};

	glfwSetKeyCallback(window, func);


	// Initialize action map. Normally this could be loaded from a json file.
	std::vector<KeyInput> keys;
	keys.push_back(KeyInput::ESC);
	keys.push_back(KeyInput::K);

	actionMap.insert(std::pair<std::string, std::vector<KeyInput>>("Escape_Action", keys));
}

void InputManager::update()
{
	glfwPollEvents();
}

void InputManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	std::cout << "Key Callback called!" << std::endl;

	std::vector<std::string> actionsToTrigger;
	// Check which actions should be called.
	for (auto& kv : actionMap)
	{
		for (auto _key : kv.second)
		{
			if (_key == key)
			{
				actionsToTrigger.push_back(kv.first);
				break;
			}
		}
	}

	for (auto& action : actionsToTrigger)
	{
		if (bindMap.find(action) != bindMap.end())
		{
			voidFuncList funcList = bindMap.at(action);
			for (auto f : funcList)
			{
				f();
			}
		}
	}
}

void InputManager::bindFunction(const std::string& action, voidFunc func)
{
	// The owner is important so that we can unbind a function later.
	auto search = bindMap.find(action);
	if (search != bindMap.end())
	{
		search->second.push_back(func);
	}
	else
	{
		voidFuncList list = {};
		list.push_back(func);
		bindMap.insert(std::pair<std::string, voidFuncList>(action, list));
	}
}

void InputManager::clearBindings(voidFunc func)
{
	for (auto& list : bindMap)
	{
		list.second.erase(std::remove_if(list.second.begin(), list.second.end(),
			[func](voidFunc curFunc) {
			return curFunc == func;
			}
		));
	}
}