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
#include <algorithm>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include "RCube.h"
#include <random>

using namespace std;

GLFWwindow* InitAll(int w = 640, int h = 480, bool Fullscreen = false);
void EndAll();
void window_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
int getState();
int getrotationmode();
vector<GLfloat*> InitVectors();
bool loadOBJ(const char* path, std::vector<glm::vec3>& outVertices, std::vector<glm::vec2>& outTextures,
	std::vector<glm::vec3>& outNormals);
string loadFile(string path);
vector<Cube> initCube();
vector<glm::vec3> getNormals();
GLfloat* peekByIndex(vector<glm::vec3> v, vector<int> indicies);
vector<char> generateRandomValuesFromArray(vector<char> v);