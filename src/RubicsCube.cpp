#include "Model.h"
#include "func.h"
#include "Shader.h"
#include "RCube.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include <thread> 
#include <chrono>   
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <memory>

using namespace std;

int WinWidth;
int WinHeight;

bool rotationmode;
const glm::mat4 WorldMatrix = glm::mat4(1.0f);


float cameraRadius = 5.0f; 
float cameraAngle = 0.0f; 
float cameraHeight = 0.0f;
int key_value = 0;
bool operationCheck = false;
bool needToUpdateAfterRotateCube = false;

glm::vec3 cameraPosition(
	cameraRadius* sin(glm::radians(cameraAngle)),
	cameraHeight, 
	cameraRadius* cos(glm::radians(cameraAngle))
);

glm::vec3 figurePosition(0.0f, 0.0f, 0.0f);

glm::mat4 getViewMatrix(glm::vec3 figurePosition) {
	return glm::lookAt(cameraPosition, figurePosition, glm::vec3(0.0f, 1.0f, 0.0f));
}

int main() {

	GLFWwindow* window = InitAll(1024, 768, false);
	if (window == nullptr)
	{
		EndAll();
		return -1;
	}

	RCube rubic;

	vector<GLfloat*> v = InitVectors();
	GLfloat* coord = v[0];
	vector<glm::vec3> normals = getNormals();
	vector<Model> models;
	rubic.setVectorOfCubes(initCube());
	auto x = rubic.getVectorOfCubes();


	for (int i = 0; i < 27; i++) {
		Model cube(window);
		cube.load_coords(coord, 36);
		cube.load_shaders("shaders/vs_3d.glsl", "shaders/fs_3d.glsl");
		cube.load_normals(normals, normals.size());
		cube.load_colors(x[i].colors, 36);
		models.push_back(cube);
	}

	Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 640);
	Mix_Chunk *down = Mix_LoadWAV("media/DownToLeftRight.wav"),
			  *up = Mix_LoadWAV("media/UpToLeftRight.wav"),
			  *left_right = Mix_LoadWAV("media/LeftRightToUpDown.wav"),
			  *front = Mix_LoadWAV("media/Front.wav"),
			  *congratulations = Mix_LoadWAV("media/GTA.wav"),
			  *main_theme = Mix_LoadWAV("media/GTA4.wav");

	glm::mat4 projMatrix = glm::perspective(
		glm::radians(25.0f), 
		(float)WinWidth / WinHeight, 
		1.0f,
		8.0f 
	);

	glm::mat4 cameraMatrix = WorldMatrix;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	rubic.zaputatCubik({ generateRandomValuesFromArray({'U','H','I','O','J','K','P','L','N','M'}) });
	rubic.updateModelMatrixs();

	glEnable(GL_DEPTH_TEST);
	Mix_PlayChannel(2, main_theme, -1);
	Mix_Volume(2, 52);

	std::vector<unsigned int> outIndices;
	
	glm::vec3 col = glm::vec3(0.0, 0.0, 0.0);
	
	glm::mat4 projMatrix_cj = glm::perspective(
		glm::radians(25.0f), 
		(float)WinWidth / WinHeight, 
		3.0f,
		8.0f 
	);

	float rotation = 0;

	while (!glfwWindowShouldClose(window))
	{
		glViewport(0, 0, WinWidth, WinHeight);  
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		if (operationCheck && rubic.getCheckNormalFace() && !rubic.getIsWin()) {
			rubic.opertionsSetup(key_value);
			Mix_PlayChannel(1, left_right, 0);
			needToUpdateAfterRotateCube = true;
		}
		if (needToUpdateAfterRotateCube) {
			rubic.updateModelMatrixs();
		}
		cameraMatrix = getViewMatrix(figurePosition);
		x = rubic.getVectorOfCubes();
		for (int i = 0; i < 27; i++) {
			models[i].render(cameraPosition, cameraMatrix, projMatrix, x[i].model_matrix, GL_TRIANGLES);
		}

		if (rubic.checkWin() && !rubic.getIsWin()) {
			cout << "Mission complete!!!" << endl;
			rubic.setIsWin(true);
			Mix_HaltChannel(2);
			Mix_PlayChannel(1, congratulations, 0);
		}

		operationCheck = false;
		needToUpdateAfterRotateCube = false;

		glfwPollEvents();
		glfwSwapBuffers(window);
		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(window, 1);
		}
		if (!rubic.getIsWin()) {
			if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_D))
			{
				rubic.setObjA_x(rubic.getObjA_x() + 0.55);
				needToUpdateAfterRotateCube = true;
			}
			if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_A))
			{
				rubic.setObjA_x(rubic.getObjA_x() - 0.55);
				needToUpdateAfterRotateCube = true;
			}
		}
		else {
			rubic.setObjA_x(rubic.getObjA_x() - 0.25);
			needToUpdateAfterRotateCube = true;
		}
	}
	return 0;
}
