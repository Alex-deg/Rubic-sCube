#include "func.h"
#include "globals.h"
#include "Points.h"
#include "Colors.h"
#include "indicies.h"

string LoadShader(const char* filename)
{
	string res;
	ifstream file(filename, ios::in);
	if (file.is_open())
	{
		std::stringstream sstr; 
		sstr << file.rdbuf(); 
		res = sstr.str(); 
		file.close(); 
	}
	return res;
}

GLFWwindow* InitAll(int w, int h, bool Fullscreen)
{
	WinWidth = w;
	WinHeight = h;
	GLFWwindow* window = nullptr;
	if (!glfwInit())
	{
		cerr << "ERROR: could not start GLFW3\n";
		exit(-1);
	}
	if (Fullscreen)
	{
		GLFWmonitor* mon = glfwGetPrimaryMonitor();
		const GLFWvidmode* vmode = glfwGetVideoMode(mon);
		WinWidth = vmode->width;
		WinHeight = vmode->height;
		window = glfwCreateWindow(WinWidth, WinHeight, "Rubic's Cube", mon, NULL);
	}
	else window = glfwCreateWindow(WinWidth, WinHeight, "Rubic's Cube", NULL, NULL);
	glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		cerr << "ERROR: could not start GLEW\n";
		return nullptr; 
	}
	return window;
}

void EndAll()
{
	glfwTerminate();
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
	WinWidth = width;
	WinHeight = height;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_W && action == GLFW_REPEAT)
	{
		if (cameraHeight < 3)
			cameraHeight += 0.5f;
	}

	else if (key == GLFW_KEY_S && action == GLFW_REPEAT)
	{
		if (cameraHeight > -3)
			cameraHeight -= 0.5f;
	}

	if (key == GLFW_KEY_MINUS && action == GLFW_REPEAT)
	{
		cameraRadius += 0.1f;
	}
	else if (key == GLFW_KEY_EQUAL && action == GLFW_REPEAT)
	{
		cameraRadius -= 0.1f;
	}

	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
		key_value = key;
		operationCheck = true;
	}
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) { 
		key_value = key;
		operationCheck = true;
	}
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) { 
		key_value = key;
		operationCheck = true;
	}
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) { 
		key_value = key;
		operationCheck = true;
	}
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) { 
		key_value = key;
		operationCheck = true;
	}
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
		key_value = key;
		operationCheck = true;
	}
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) { 
		key_value = key;
		operationCheck = true;
	}
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) { 
		key_value = key;
		operationCheck = true;
	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		key_value = key;
		operationCheck = true;
	}
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) { 
		key_value = key;
		operationCheck = true;
	}
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) { 
		key_value = key;
		operationCheck = true;
	}

	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) { 
		key_value = key;
		operationCheck = true;
	}

	cameraPosition.x = cameraRadius * sin(glm::radians(cameraAngle));
	cameraPosition.y = cameraHeight;
	cameraPosition.z = cameraRadius * cos(glm::radians(cameraAngle));

}

vector<char> generateRandomValuesFromArray(vector<char> v) {
	std::random_device rd;
	std::mt19937 gen(rd());
	uniform_int_distribution<> distrib(0, 99);
	vector<char> res;
	int count = distrib(gen) % 8 + 8;
	for (int i = 0; i < count; i++) {
		res.push_back(v[distrib(gen) % v.size()]);
	}
	return res;
}

int getState()
{
	return state;
}

int getrotationmode()
{
	return rotationmode;
}

vector<GLfloat*> InitVectors() {
	vector<GLfloat*> res;
	res = { peekByIndex(points, indices) };
	std::cout << res[0] << std::endl;
	return res;
}
					
GLfloat* ChooseCoordinatesByIndex(GLfloat* arr, vector<int> indexs)
{
	GLfloat* result = new GLfloat[3 * indexs.size()];
	for (int i = 0; i < indexs.size(); i++) {
		result[3 * i] = arr[(indexs[i] - 1) * 3];
		result[i * 3 + 1] = arr[(indexs[i] - 1) * 3 + 1];
		result[i * 3 + 2] = arr[(indexs[i] - 1) * 3 + 2];
	}
	return result;
}
		
bool loadOBJ(
	const char* path,
	std::vector<glm::vec3>& outVertices,
	std::vector<glm::vec2>& outTextures,
	std::vector<glm::vec3>& outNormals
)
{
	std::vector< unsigned int > vertexIndices, vtIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_textures;
	std::vector< glm::vec3 > temp_normals;
	string buf;
	string buf1;
	int co = 0;
	std::stringstream sstr;
	bool cont = false;
	ifstream file(path, ios::in);
	if (file.is_open())
	{
		sstr << file.rdbuf();
		file.close();
	}
	else return false;
	outNormals.clear();
	outVertices.clear();
	outTextures.clear();

	while (cont || sstr >> buf)
	{
		cont = false;
		if (buf == "v")
		{
			glm::vec3 vertex;
			sstr >> vertex.x;
			sstr >> vertex.y;
			sstr >> vertex.z;
			temp_vertices.push_back(vertex);
		}
		else if (buf == "vt")
		{
			glm::vec2 texture;
			sstr >> texture.x;
			sstr >> texture.y;
			temp_textures.push_back(texture);
		}
		else if (buf == "vn")
		{
			glm::vec3 normal;
			sstr >> normal.x;
			sstr >> normal.y;
			sstr >> normal.z;
			temp_normals.push_back(normal);
		}
		else if (buf == "f")
		{
			vector<string> vertexes;
			vector<int> vertindexes;
			while (!cont)
			{
				sstr >> buf;
				if (buf.find('/') != string::npos) {
					vertexes.push_back(buf);
					if (sstr.eof())
					{
						for (string vert : vertexes)
						{
							std::replace(vert.begin(), vert.end(), '/', ' ');
							std::stringstream tmpstream(vert);
							int v, vt, n;
							tmpstream >> v;
							tmpstream >> vt;
							tmpstream >> n;
							vertindexes.push_back(v);
							vertindexes.push_back(vt);
							vertindexes.push_back(n);
						}
						for (int i = 0; i < 3; i++)
						{
							vertexIndices.push_back(vertindexes[i * 3 + 0]);
							vtIndices.push_back(vertindexes[i * 3 + 1]);
							normalIndices.push_back(vertindexes[i * 3 + 2]);
						}
						size_t tmpsize = vertexes.size();

						if (tmpsize > 3)
						{
							for (int i = 3; i < tmpsize; i++)
							{
								vertexIndices.push_back(vertindexes[0]);
								vtIndices.push_back(vertindexes[1]);
								normalIndices.push_back(vertindexes[2]);
								vertexIndices.push_back(vertindexes[(i - 1) * 3 + 0]);
								vtIndices.push_back(vertindexes[(i - 1) * 3 + 1]);
								normalIndices.push_back(vertindexes[(i - 1) * 3 + 2]);
								vertexIndices.push_back(vertindexes[i * 3 + 0]);
								vtIndices.push_back(vertindexes[i * 3 + 1]);
								normalIndices.push_back(vertindexes[i * 3 + 2]);
							}

						}
						cont = true;
					}
				}
				else
				{
					for (string vert : vertexes)
					{
						std::replace(vert.begin(), vert.end(), '/', ' ');
						std::stringstream tmpstream(vert);
						int v, vt, n;
						tmpstream >> v;
						tmpstream >> vt;
						tmpstream >> n;
						vertindexes.push_back(v);
						vertindexes.push_back(vt);
						vertindexes.push_back(n);
					}
					for (int i = 0; i < 3; i++)
					{
						vertexIndices.push_back(vertindexes[i * 3 + 0]);
						vtIndices.push_back(vertindexes[i * 3 + 1]);
						normalIndices.push_back(vertindexes[i * 3 + 2]);
					}
					size_t tmpsize = vertexes.size();

					if (tmpsize > 3)
					{
						for (int i = 3; i < tmpsize; i++)
						{
							vertexIndices.push_back(vertindexes[0]);
							vtIndices.push_back(vertindexes[1]);
							normalIndices.push_back(vertindexes[2]);
							vertexIndices.push_back(vertindexes[(i - 1) * 3 + 0]);
							vtIndices.push_back(vertindexes[(i - 1) * 3 + 1]);
							normalIndices.push_back(vertindexes[(i - 1) * 3 + 2]);
							vertexIndices.push_back(vertindexes[i * 3 + 0]);
							vtIndices.push_back(vertindexes[i * 3 + 1]);
							normalIndices.push_back(vertindexes[i * 3 + 2]);
						}

					}
					cont = true;
				}
			}
		}
	}
	size_t tmpsize = vertexIndices.size();
	for (unsigned int i = 0; i < tmpsize; i++)
	{
		glm::vec3 vertex = temp_vertices[vertexIndices[i] - 1];
		outVertices.push_back(vertex);
		glm::vec3 normal = temp_normals[normalIndices[i] - 1];
		outNormals.push_back(normal);
		glm::vec2 vt = temp_textures[vtIndices[i] - 1];
		outTextures.push_back(vt);
	}
	return true;
}


string loadFile(string path) {
	ifstream file(path);
	string str = "";
	string file_contents = "";
	while (getline(file, str))
	{
		file_contents += str;
		file_contents.push_back('\n');
	}
	return file_contents;
}

vector<Cube> initCube() {

	vector <Cube> v;
	Cube cur;
	Point p;

	glm::mat4 curMM;
	for (int i = 0; i < 27; i++) {
		curMM = glm::mat4(1.0);
		curMM = glm::translate(curMM, vectors_to_translate[i]);
		curMM = glm::scale(curMM, glm::vec3(0.3, 0.3, 0.3));
		cur.model_matrix = curMM;
		cur.matrix_rotate = glm::mat4(1.0);
		cur.v = vectors_to_translate[i];
		cur.rotated_by_instructions = cur.v;
		p.level = i / 9;
		p.x = (i - p.level * 9) / 3;
		p.y = (i - p.level * 9 - p.x * 3) % 3;
		cur.p = p;
		cur.colors = peekByIndex(colors, colors_for_each_cube[i]);
		v.push_back(cur);
	}
	return v;

}

vector<glm::vec3> getNormals()
{
	return normals;
}

GLfloat* peekByIndex(vector<glm::vec3> v, vector<int> indicies) {
	GLfloat* result = new GLfloat[3 * indicies.size()];
	int it = 0;
	for (auto index : indicies) {
		for (int j = 0; j < 3; j++) {
			result[it] = v[index][j]; 
			it++;
		}
	}
	return result;
}

