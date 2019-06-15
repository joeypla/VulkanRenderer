#pragma once
#include <string>
#include "Graphics.h"
#include <glm/glm.hpp>
class Shader
{
public:
	Shader();
	~Shader();
	bool load(const std::string& vertexPath, const std::string& fragPath);
	void use();

	GLuint programId;

	void setFloat(const std::string& name, float value);
	void setVec3(const std::string& name, glm::vec3 vec);
	void setMat4(const std::string& name, glm::mat4 matrix);

};