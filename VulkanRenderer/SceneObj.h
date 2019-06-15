#pragma once

#include <glm/glm.hpp>
class SceneObj
{
public:
	SceneObj();
	~SceneObj();
	virtual void update(float deltaTime);
};