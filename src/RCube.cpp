#include "RCube.h"

void RCube::setVectorOfCubes(std::vector<Cube> v) {
	c.clear();
	for (auto &x : v) {
		c.push_back(x);
	}
}

std::vector<Cube> RCube::getVectorOfCubes() {
	return c;
}

void RCube::updateModelMatrixs() { 
	for (auto &el : c) {
		el.model_matrix = glm::mat4(1.0);
		el.model_matrix = glm::translate(el.model_matrix, rotateTranslateVector(el));
		el.model_matrix *= el.matrix_rotate;
		el.model_matrix = podkrut(el);
		el.model_matrix = glm::scale(el.model_matrix, glm::vec3(0.3, 0.3, 0.3));
	}
}

glm::vec3 RCube::rotateTranslateVector(Cube c) {
	c.cur = c.rotated_by_instructions;
	c.cur = rotateIn3D(c.cur, 'y', objA_x);
	return c.cur;
}

bool optimizationForPushBacksInInstructions(Cube c, char axis, float angle) {
	if (c.instuctions.size() > 0 && c.instuctions[c.instuctions.size() - 1].first == axis && c.instuctions[c.instuctions.size() - 1].second == -angle) {
		c.instuctions.erase(c.instuctions.end() - 1);
		return false;
	}
	return true;
}

void RCube::zaputatCubik(std::vector<char> v) {
	for (auto& x : v) {
		opertionsSetup(x);
	}
}

void RCube::reverseCube()
{
	std::pair<char, float> p;
	for (auto& x : c) {
		switch(cur_front_face){
		case 'G':
			p = { 'z', -90 };
			break;
		case 'Y':
			p = { 'x', -90 };
			break;
		case 'W':
			p = { 'x', 90 };
			break;
		case 'B':
			p = { 'z', 90 };
			break;
		}
		std::pair<char, char> point;
		for (int i = 0; i < 2; i++) {
			point = rotateIn2D(x.p.level, x.p.y, -90);
			x.p.level = point.first + 1;
			x.p.y = point.second + 1;
			x.instuctions.push_back(p);
			x.rotated_by_instructions = rotateIn3D(x.rotated_by_instructions, p.first, p.second);
			x.matrix_rotate = rotateCube(x, p);
		}
	}
	if (cur_up_face == 'O')
		cur_up_face = 'R';
	else cur_up_face = 'R';
}

void RCube::rightToUp() {
	
	std::pair<char, float> p;
	for (auto& x : c) {
		if (x.p.y == 2) {
			switch (cur_front_face)
			{
			case 'G':
				p = { 'x', -90 };
				break;
			case 'Y':
				p = { 'z', -90 };
				break;
			case 'W':
				p = { 'z', 90 };
				break;
			case 'B':
				p = { 'x', 90 };
				break;
			}
			auto point = rotateIn2D(x.p.level, x.p.x, -90.0);
			x.p.level = point.first + 1;
			x.p.x = point.second + 1;
			x.instuctions.push_back(p);
			x.rotated_by_instructions = rotateIn3D(x.rotated_by_instructions, p.first, p.second);
			x.matrix_rotate = rotateCube(x, p);
		}
	}
	
}

void RCube::rightToDown()
{
	std::pair<char, float> p;
	for (auto& x : c) {
		if (x.p.y == 2) {
			switch (cur_front_face)
			{
			case 'G':
				p = { 'x', 90 };
				break;
			case 'Y':
				p = { 'z', 90 };
				break;
			case 'W':
				p = { 'z', -90 };
				break;
			case 'B':
				p = { 'x', -90 };
				break;
			}
			auto point = rotateIn2D(x.p.level, x.p.x, 90.0);
			x.p.level = point.first + 1;
			x.p.x = point.second + 1;
			x.instuctions.push_back(p);
			x.rotated_by_instructions = rotateIn3D(x.rotated_by_instructions, p.first, p.second);
			x.matrix_rotate = rotateCube(x, p);
		}
	}
}

void RCube::leftToUp()
{
	std::pair<char, float> p;
	for (auto& x : c) {
		if (x.p.y == 0) {
			switch (cur_front_face)
			{
			case 'G':
				p = { 'x', -90 };
				break;
			case 'Y':
				p = { 'z', -90 };
				break;
			case 'W':
				p = { 'z', 90 };
				break;
			case 'B':
				p = { 'x', 90 };
				break;
			}
			auto point = rotateIn2D(x.p.level, x.p.x, -90.0);
			x.p.level = point.first + 1;
			x.p.x = point.second + 1;
			x.instuctions.push_back(p);
			x.rotated_by_instructions = rotateIn3D(x.rotated_by_instructions, p.first, p.second);
			x.matrix_rotate = rotateCube(x, p);
		}
	}
}

void RCube::leftToDown()
{
	std::pair<char, float> p;
	for (auto& x : c) {
		if (x.p.y == 0) {
			switch (cur_front_face)
			{
			case 'G':
				p = { 'x', 90 };
				break;
			case 'Y':
				p = { 'z', 90 };
				break;
			case 'W':
				p = { 'z', -90 };
				break;
			case 'B':
				p = { 'x', -90 };
				break;
			}
			auto point = rotateIn2D(x.p.level, x.p.x, 90.0);
			x.p.level = point.first + 1;
			x.p.x = point.second + 1;
			x.instuctions.push_back(p);
			x.rotated_by_instructions = rotateIn3D(x.rotated_by_instructions, p.first, p.second);
			x.matrix_rotate = rotateCube(x, p);
		}
	}
}

void RCube::upToLeft()
{
	for (auto& x : c) {
		if (x.p.level == 0) {
			auto point = rotateIn2D(x.p.x, x.p.y, 90.0);
			x.p.x = point.first + 1;
			x.p.y = point.second + 1;
			x.instuctions.push_back({ 'y', -90 });
			x.rotated_by_instructions = rotateIn3D(x.rotated_by_instructions, 'y', -90);
			x.matrix_rotate = rotateCube(x, { 'y', -90 });
		}
	}
}

void RCube::upToRight()
{
	for (auto& x : c) {
		if (x.p.level == 0) {
			auto point = rotateIn2D(x.p.x, x.p.y, -90.0);
			x.p.x = point.first + 1;
			x.p.y = point.second + 1;
			x.instuctions.push_back({ 'y', 90 });
			x.rotated_by_instructions = rotateIn3D(x.rotated_by_instructions, 'y', 90);
			x.matrix_rotate = rotateCube(x, { 'y', 90 });
		}
	}
}

void RCube::downToLeft()
{
	for (auto& x : c) {
		if (x.p.level == 2) {
			auto point = rotateIn2D(x.p.x, x.p.y, 90.0);
			x.p.x = point.first + 1;
			x.p.y = point.second + 1;
			x.instuctions.push_back({ 'y', -90 });
			x.rotated_by_instructions = rotateIn3D(x.rotated_by_instructions, 'y', -90);
			x.matrix_rotate = rotateCube(x, { 'y', -90 });
		}
	}
}

void RCube::downToRight()
{
	for (auto& x : c) {
		if (x.p.level == 2) {
			auto point = rotateIn2D(x.p.x, x.p.y, -90.0);
			x.p.x = point.first + 1;
			x.p.y = point.second + 1;
			x.instuctions.push_back({ 'y', 90 });
			x.rotated_by_instructions = rotateIn3D(x.rotated_by_instructions, 'y', 90);
			x.matrix_rotate = rotateCube(x, {'y', 90});
		}
	}
}

void RCube::frontPoChas()
{
	std::pair<char, float> p;
	for (auto& x : c) {
		if (x.p.x == 0) {
			switch (cur_front_face)
			{
			case 'G':
				p = { 'z', -90 };
				break;
			case 'Y':
				p = { 'x', 90 };
				break;
			case 'W':
				p = { 'x', -90 };
				break;
			case 'B':
				p = { 'z', 90 };
				break;
			}
			auto point = rotateIn2D(x.p.level, x.p.y, -90.0);
			x.p.level = point.first + 1;
			x.p.y = point.second + 1;
			x.instuctions.push_back(p);
			x.rotated_by_instructions = rotateIn3D(x.rotated_by_instructions, p.first, p.second);
			x.matrix_rotate = rotateCube(x, p);
		}
	}
}

void RCube::frontProtivChas()
{
	std::pair<char, float> p;
	for (auto& x : c) {
		if (x.p.x == 0) {
			switch (cur_front_face)
			{
			case 'G':
				p = { 'z', 90 };
				break;
			case 'Y':
				p = { 'x', -90 };
				break;
			case 'W':
				p = { 'x', 90 };
				break;
			case 'B':
				p = { 'z', -90 };
				break;
			}
			auto point = rotateIn2D(x.p.level, x.p.y, 90.0);
			x.p.level = point.first + 1;
			x.p.y = point.second + 1;
			x.instuctions.push_back(p);
			x.rotated_by_instructions = rotateIn3D(x.rotated_by_instructions, p.first, p.second);
			x.matrix_rotate = rotateCube(x, p);
		}
	}
}

glm::mat4 RCube::rotateCube(Cube &c, std::pair<char, float> x) {
	std::map<int, glm::vec3> m = {
		{120, glm::vec3(1.0, 0.0, 0.0)},
		{121, glm::vec3(0.0, 1.0, 0.0)},
		{122, glm::vec3(0.0, 0.0, 1.0)}
	};
	int tmp;
	switch (x.first)
	{
	case 120:
		if (c.local_axis[1] < 0)
			c.matrix_rotate = glm::rotate(c.matrix_rotate, glm::radians(-x.second), m[-c.local_axis[1]]);
		else c.matrix_rotate = glm::rotate(c.matrix_rotate, glm::radians(x.second), m[c.local_axis[1]]);
		if (x.second > 0) {
			tmp = c.local_axis[0];
			c.local_axis[0] = -c.local_axis[2];
			c.local_axis[2] = tmp;
		}
		else {
			tmp = c.local_axis[2];
			c.local_axis[2] = -c.local_axis[0];
			c.local_axis[0] = tmp;
		}
		break;
	case 121:
		if (c.local_axis[0] < 0)
			c.matrix_rotate = glm::rotate(c.matrix_rotate, glm::radians(-x.second), m[-c.local_axis[0]]);
		else c.matrix_rotate = glm::rotate(c.matrix_rotate, glm::radians(x.second), m[c.local_axis[0]]);
		if (x.second > 0) {
			tmp = c.local_axis[2];
			c.local_axis[2] = -c.local_axis[1];
			c.local_axis[1] = tmp;
		}
		else {
			tmp = c.local_axis[1];
			c.local_axis[1] = -c.local_axis[2];
			c.local_axis[2] = tmp;
		}
		break;
	case 122:
		if (c.local_axis[2] < 0)
			c.matrix_rotate = glm::rotate(c.matrix_rotate, glm::radians(-x.second), m[-c.local_axis[2]]);
		else c.matrix_rotate = glm::rotate(c.matrix_rotate, glm::radians(x.second), m[c.local_axis[2]]);
		if (x.second > 0) {
			tmp = c.local_axis[1];
			c.local_axis[1] = -c.local_axis[0];
			c.local_axis[0] = tmp;
		}
		else {
			tmp = c.local_axis[0];
			c.local_axis[0] = -c.local_axis[1];
			c.local_axis[1] = tmp;
		}
		break;
	}
	return c.matrix_rotate;
}

glm::mat4 RCube::podkrut(Cube c) {
	std::map<int, glm::vec3> m = {
		{120, glm::vec3(1.0, 0.0, 0.0)},
		{121, glm::vec3(0.0, 1.0, 0.0)},
		{122, glm::vec3(0.0, 0.0, 1.0)}
	};
	if (c.local_axis[0] < 0)
		c.model_matrix = glm::rotate(c.model_matrix, glm::radians(-objA_x), m[-c.local_axis[0]]);
	else c.model_matrix = glm::rotate(c.model_matrix, glm::radians(objA_x), m[c.local_axis[0]]);
	return c.model_matrix;
}

glm::mat4 RCube::rotateCubes(Cube c) {
	std::vector<int> axis = { 121, 120, 122 }; 
	std::map<int, glm::vec3> m = {
		{120, glm::vec3(1.0, 0.0, 0.0)},
		{121, glm::vec3(0.0, 1.0, 0.0)},
		{122, glm::vec3(0.0, 0.0, 1.0)}
	};
	int tmp;
	c.model_matrix = glm::mat4(1.0);
	for (auto& x : c.instuctions) {
		switch (x.first)
		{
		case 120:
			if (axis[1] < 0)
				c.model_matrix = glm::rotate(c.model_matrix, glm::radians(-x.second), m[-axis[1]]);
			else c.model_matrix = glm::rotate(c.model_matrix, glm::radians(x.second), m[axis[1]]);
			if (x.second > 0) {
				tmp = axis[0];
				axis[0] = -axis[2];
				axis[2] = tmp;
			}
			else {
				tmp = axis[2];  
				axis[2] = -axis[0];
				axis[0] = tmp;
			}
			break;
		case 121:
			if (axis[0] < 0)
				c.model_matrix = glm::rotate(c.model_matrix, glm::radians(-x.second), m[-axis[0]]);
			else c.model_matrix = glm::rotate(c.model_matrix, glm::radians(x.second), m[axis[0]]);
			if (x.second > 0) {
				tmp = axis[2];
				axis[2] = -axis[1];
				axis[1] = tmp;
			}
			else {
				tmp = axis[1];
				axis[1] = -axis[2];
				axis[2] = tmp;
			}
			break;
		case 122:
			if (axis[2] < 0)
				c.model_matrix = glm::rotate(c.model_matrix, glm::radians(-x.second), m[-axis[2]]);
			else c.model_matrix = glm::rotate(c.model_matrix, glm::radians(x.second), m[axis[2]]);
			if (x.second > 0) {
				tmp = axis[1];
				axis[1] = -axis[0];
				axis[0] = tmp;
			}
			else {
				tmp = axis[0];
				axis[0] = -axis[1];
				axis[1] = tmp;
			}
			break;
		}
	}
	if(axis[0] < 0)
		c.model_matrix = glm::rotate(c.model_matrix, glm::radians(-objA_x), m[-axis[0]]);
	else c.model_matrix = glm::rotate(c.model_matrix, glm::radians(objA_x), m[axis[0]]);
	return c.model_matrix;
}

void RCube::setObjA_x(float a_x)
{
	objA_x = normalizeAngle(a_x);
	prev_front_face = cur_front_face;
	cur_front_face = whatGran();
	if (cur_front_face != prev_front_face)
		changeMassiveOfPoints();
}

void RCube::setCurFrontFace(char c)
{
	cur_front_face = c;
}

void RCube::setPrevFrontFace(char c)
{
	prev_front_face = c;
}

void RCube::setIsWin(bool flag)
{
	isWin = flag;
}

float RCube::getObjA_x()
{
	return objA_x;
}

char RCube::getCurFrontFace()
{
	return cur_front_face;
}

char RCube::getPrevFrontFace()
{
	return prev_front_face;
}

bool RCube::getCheckNormalFace()
{
	return checkNormaleFace;
}

bool RCube::getIsWin()
{
	return isWin;
}

bool RCube::checkWin() {
	for (auto& x : c) {
		if (!(x.v.x == normalizefloat(x.rotated_by_instructions.x) && 
			  x.v.y == normalizefloat(x.rotated_by_instructions.y) && 
			  x.v.z == normalizefloat(x.rotated_by_instructions.z)))
			return false;
	}
	return true;
}

float RCube::normalizefloat(float x)
{
	if (x < 0.33 && x > 0 || x > -0.33 && x < 0)
		return 0;
	else return x;
}

void RCube::opertionsSetup(int key_value)
{
	switch (key_value) {
	case 'U':
		leftToUp();
		break;
	case 'H':
		leftToDown();
		break;
	case 'I':
		upToLeft();
		break;
	case 'O':
		upToRight();
		break;
	case 'J':
		downToLeft();
		break;
	case 'K':
		downToRight();
		break;
	case 'P':
		rightToUp();
		break;
	case 'L':
		rightToDown();
		break;
	case 'R':
		reverseCube();
		break;
	case 'N':
		frontPoChas();
		break;
	case 'M':
		frontProtivChas();
		break;
	case 'Z':
		system("clear");
		for (auto& x : c) {
			cout << x.v.x << " " << x.v.y << " " << x.v.z << endl;
			cout << normalizefloat(x.rotated_by_instructions.x) << " " << normalizefloat(x.rotated_by_instructions.y) << " " << normalizefloat(x.rotated_by_instructions.z) << endl;
		}
		break;
	}
}

std::pair<char, char> RCube::rotateIn2D(char x, char y, float angle)
{
	std::pair<char, char> res;
	x--;
	y--;
	res.first = -y * sin(glm::radians(angle));
	res.second = x * sin(glm::radians(angle));
	return res;
}

glm::vec3 multiplyMatrixAndVector(std::vector<std::vector<float>> m, glm::vec3 v) {

	glm::vec3 result = { 0.0, 0.0, 0.0 };
	for (int i = 0; i < m[0].size(); i++) {
		result.x += m[0][i] * v[i];
	}
	for (int i = 0; i < m[1].size(); i++) {
		result.y += m[1][i] * v[i];
	}
	for (int i = 0; i < m[2].size(); i++) {
		result.z += m[2][i] * v[i];
	}
	return result;
}

glm::vec3 RCube::rotateIn3D(glm::vec3 v, char axis, float angle)
{
	std::vector<std::vector<float>> rotate_matrix;
	switch (axis) {
	case 'x':
		rotate_matrix = {
			{ 1, 0, 0 },
			{ 0, cos(glm::radians(angle)), -sin(glm::radians(angle)) },
			{ 0, sin(glm::radians(angle)), cos(glm::radians(angle)) },
		};
		break;
	case 'y':
		rotate_matrix = {
			{ cos(glm::radians(angle)), 0, sin(glm::radians(angle)) },
			{ 0, 1, 0 },
			{ -sin(glm::radians(angle)), 0, cos(glm::radians(angle)) },
		};
		break;
	case 'z':
		rotate_matrix = {
			{ cos(glm::radians(angle)), -sin(glm::radians(angle)), 0},
			{ sin(glm::radians(angle)), cos(glm::radians(angle)), 0},
			{ 0, 0, 1},
		};
		break;
	}
	return multiplyMatrixAndVector(rotate_matrix, v);
}

float RCube::normalizeAngle(float ang)
{
	if (ang >= 360)
		ang -= 360;
	else {
		if (ang <= -360)
			ang += 360;
	}
	return ang;
}

void RCube::changeMassiveOfPoints() {
	switch (cur_front_face) {
	case 'G':
		if (prev_front_face == 'Y')
			rotateMassiveOfPointsToRight();
		if (prev_front_face == 'W')
			rotateMassiveOfPointsToLeft();
		break;
	case 'Y':
		if (prev_front_face == 'G')
			rotateMassiveOfPointsToLeft();
		if (prev_front_face == 'B')
			rotateMassiveOfPointsToRight();
		break;
	case 'B':
		if (prev_front_face == 'Y')
			rotateMassiveOfPointsToLeft();
		if (prev_front_face == 'W')
			rotateMassiveOfPointsToRight();
		break;
	case 'W':
		if (prev_front_face == 'G')
			rotateMassiveOfPointsToRight();
		if (prev_front_face == 'B')
			rotateMassiveOfPointsToLeft();
		break;
	}
}

void RCube::rotateMassiveOfPointsToRight()
{
	for (auto& el : c) {
		auto point = rotateIn2D(el.p.x, el.p.y, 90.0);
		el.p.x = point.first + 1;
		el.p.y = point.second + 1;
	}
}

void RCube::rotateMassiveOfPointsToLeft()
{
	for (auto& el : c) {
		auto point = rotateIn2D(el.p.x, el.p.y, -90.0);
		el.p.x = point.first + 1;
		el.p.y = point.second + 1;
	}
}

char RCube::whatGran() 
{
	checkNormaleFace = true;
	if (objA_x > -10 && objA_x < 10 || objA_x > 350) // G - green, Y - yellow, B - blue, W - white, N - ne tochnost
		return 'G';
	if (objA_x > 80 && objA_x < 100)
		return 'Y';
	if (objA_x > 170 && objA_x < 190)
		return 'B';
	if (objA_x > 260 && objA_x < 280)
		return 'W';

	if (objA_x > -10 && objA_x < 10 || objA_x < -350)
		return 'G';
	if (objA_x < -80 && objA_x > -100)
		return 'W';
	if (objA_x < -170 && objA_x > -190)
		return 'B';
	if (objA_x < -260 && objA_x > -280)
		return 'Y';
	checkNormaleFace = false;
	return cur_front_face;
}

