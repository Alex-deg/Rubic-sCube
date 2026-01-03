#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;
class Model
{
public:
	Model(GLFWwindow* w) {
		glGenVertexArrays(1, &vao);
		window = w;
	};
	~Model() {};
	void render(glm::vec3 camPosition, glm::mat4 VMatrix, glm::mat4 PMatrix, glm::mat4 MMatrix, GLuint mode);
	void render(glm::mat4 VMatrix, glm::mat4 PMatrix, glm::mat4 MMatrix, GLuint mode);
	void load_coords(GLfloat* verteces, size_t count);
	void load_coords(std::vector<glm::vec3>& verteces, size_t count);
	void load_colors(GLfloat* colors, size_t count);
	void load_indices(GLuint* indices, size_t count);
	void load_shaders(const char* vect, const char* frag);
	void load_textures(const std::vector<glm::vec2>& tex, size_t count);
	void load_normals(const std::vector <glm::vec3>& normals, size_t count);
private:
	GLuint vao = -1;
	size_t verteces_count = 0;
	size_t indices_count = 0;
	GLuint shader_programme = -1;
	GLFWwindow* window;
};