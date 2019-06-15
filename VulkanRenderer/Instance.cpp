#include "Instance.h"
#include "GraphicsLayer.h"
#include "InputManager.h"

Instance::Instance()
{
	shouldExit = false;
}

Instance* Instance::instance = nullptr;
Instance* Instance::get()
{
	if (!instance)
	{
		instance = new Instance();
	}

	return instance;
}


void Instance::run()
{
	GraphicsLayer graphics;

	// The graphics was responsible for creating the window context used for drawing. It is also
	// the context that is accepting input.
	InputManager input(graphics.getWindow());

	// We want to make sure that we capture the escape key and exit if we need to.
	// ----------------------------------------------------------------------------------
	// So this works with the bind out here. I'd like to figure out how to get the bind inside, this way
	// I just have to pass this and member function instead of calling bind out here. I don't understand this
	// well enough yet, so I'm actually not even sure if its possible.
	input.bindFunction("Escape_Action", &Instance::OnExit);
	

	do {
		input.update();
		graphics.render();
		
	} while (!shouldExit);
}

void Instance::OnExit()
{
	Instance* instance = Instance::get();
	if (instance)
	{
		instance->shouldExit = true;
	}
}