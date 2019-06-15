#include "Instance.h"

#include <iostream>
#include <stdexcept>

#include <chrono>
struct TestData {
	float x;
	float y;
	float z;
	float dx;
	float dy;
	float dz;

	TestData()
	{
		x = 0.f;
		y = 0.f;
		z = 0.f;
		dx = 1.0f;
		dy = 1.0f;
		dz = 1.0f;
	}
};

struct TimingHelper
{
	std::chrono::time_point<std::chrono::steady_clock> start;
	std::string _tag;
	TimingHelper(std::string tag)
	{
		_tag = tag;
		start = std::chrono::high_resolution_clock::now();
	}
	~TimingHelper()
	{
		auto finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> elapsed = finish - start;
		std::cout << _tag.c_str() << ": " << elapsed.count() << "ms" << std::endl;
	}
};

int main()
{

	Instance* instance = Instance::get();

	try {
		instance->run();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}