#pragma once
#include <map>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

struct Point {
	char level;
	char x;
	char y;
};

struct Cube {
	glm::mat4 model_matrix, matrix_rotate;
	Point p;
	glm::vec3 v, rotated_by_instructions, cur; 
	GLfloat* colors;
	vector<int> local_axis = { 121, 120, 122 };
	std::vector<std::pair<char, float>> instuctions;
};

class RCube
{
private:
	std::vector<Cube> c; 
	char cur_front_face = 'G', prev_front_face = 'N', cur_up_face = 'O';
	bool isWin = false;
	float objA_x = 0;
	bool checkNormaleFace = true;
public:
	void setVectorOfCubes(std::vector<Cube> v);
	std::vector<Cube> getVectorOfCubes();
	void updateModelMatrixs();
	void rightToUp();
	void rightToDown();
	void leftToUp();
	void leftToDown();
	void upToLeft();
	void upToRight();
	void downToLeft();
	void downToRight();
	void frontPoChas();
	void frontProtivChas();

	void setObjA_x(float a_x);
	void setCurFrontFace(char c);
	void setPrevFrontFace(char c);
	void setIsWin(bool flag);
	float getObjA_x();
	char getCurFrontFace();
	char getPrevFrontFace();
	bool getCheckNormalFace();
	bool getIsWin();

	void opertionsSetup(int key_value);

	char whatGran();
	void changeMassiveOfPoints();

	void rotateMassiveOfPointsToRight();
	void rotateMassiveOfPointsToLeft();

	std::pair<char, char> rotateIn2D(char x, char y, float angle);

	glm::vec3 rotateIn3D(glm::vec3 v, char axis, float angle);

	float normalizeAngle(float ang);

	glm::vec3 rotateTranslateVector(Cube c);
	glm::mat4 rotateCubes(Cube c);

	void zaputatCubik(std::vector<char> v);

	void reverseCube();
	bool checkWin();


	glm::mat4 rotateCube(Cube &c, std::pair<char, float> x);
	glm::mat4 podkrut(Cube c);
	float normalizefloat(float x);

};

