#pragma once

#include <vector>
#include "Graphics.h"
#include <glm/glm.hpp>
struct MeshVertex
{
	glm::vec3 pos;
	float testfloat;

	glm::vec3 normal;
	float anotherfloat;
};
class Mesh
{
public:
	Mesh();

	bool load(const std::string& path);
	void draw();
private:
	std::vector<MeshVertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<glm::vec2> uvs;

	GLuint VBO;
	GLuint VAO;

	void setup();
};