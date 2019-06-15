#pragma once

class Instance
{
public:
	Instance();
	static Instance* instance;
	static Instance* get();

	/* Begins the core loop */
	void run();
private:
	bool shouldExit;

	static void OnExit();
};