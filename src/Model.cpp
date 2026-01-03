#include "Model.h"
#include "func.h"

void Model::render(glm::vec3 camPosition, glm::mat4 VMatrix, glm::mat4 PMatrix, glm::mat4 MMatrix, GLuint mode)
{
	glUseProgram(shader_programme);	

	GLuint M = glGetUniformLocation(shader_programme, "M");
	glUniformMatrix4fv(M, 1, GL_FALSE, &MMatrix[0][0]);
	GLuint P = glGetUniformLocation(shader_programme, "P");
	glUniformMatrix4fv(P, 1, GL_FALSE, &PMatrix[0][0]);
	GLuint V = glGetUniformLocation(shader_programme, "V");
	glUniformMatrix4fv(V, 1, GL_FALSE, &VMatrix[0][0]);

	GLuint lightPos = glGetUniformLocation(shader_programme, "light.position");
	glUniform3f(lightPos, 0.0f, 3.0f, 3.0f);

	GLuint lightDirection = glGetUniformLocation(shader_programme, "light.direction");
	glUniform3f(lightDirection, 0.0f, 0.0f, 0.0f);

	GLuint viewPos = glGetUniformLocation(shader_programme, "viewPos");
	glUniform3fv(viewPos, 1, glm::value_ptr(camPosition));

	GLuint lightAmbient = glGetUniformLocation(shader_programme, "light.ambient");
	glUniform3f(lightAmbient, 0.3f, 0.3f, 0.3f);

	GLuint lightDiffuse = glGetUniformLocation(shader_programme, "light.diffuse");
	glUniform3f(lightDiffuse, 0.8f, 0.8f, 0.8f);

	GLuint lightSpecular = glGetUniformLocation(shader_programme, "light.specular");
	glUniform3f(lightSpecular, 1.0f, 1.0f, 1.0f);

	GLuint lightConstant = glGetUniformLocation(shader_programme, "light.constant");
	glUniform1f(lightConstant, 1.0f);

	GLuint lightLinear = glGetUniformLocation(shader_programme, "light.linear");
	glUniform1f(lightLinear, 0.09f);

	GLuint lightQuadratic = glGetUniformLocation(shader_programme, "light.quadratic");
	glUniform1f(lightQuadratic, 0.032f);

	glBindVertexArray(vao);
	if (indices_count > 0)
		glDrawElements(mode, indices_count, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(mode, 0, verteces_count);
}

void Model::render(glm::mat4 VMatrix, glm::mat4 PMatrix, glm::mat4 MMatrix, GLuint mode)
{

	glUseProgram(shader_programme);

	GLuint M = glGetUniformLocation(shader_programme, "M");
	glUniformMatrix4fv(M, 1, GL_FALSE, &MMatrix[0][0]);
	GLuint P = glGetUniformLocation(shader_programme, "P");
	glUniformMatrix4fv(P, 1, GL_FALSE, &PMatrix[0][0]);
	GLuint V = glGetUniformLocation(shader_programme, "V");
	glUniformMatrix4fv(V, 1, GL_FALSE, &VMatrix[0][0]);

	glBindVertexArray(vao);
	if (indices_count > 0)
		glDrawElements(mode, indices_count, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(mode, 0, verteces_count);
}

void Model::load_coords(GLfloat* verteces, size_t count)
{
	verteces_count = count;
	GLuint coords_vbo = 0;
	glGenBuffers(1, &coords_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, coords_vbo);
	glBufferData(GL_ARRAY_BUFFER, 3 * count * sizeof(GLfloat), verteces, GL_STATIC_DRAW);
	glBindVertexArray(vao);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
}

void Model::load_coords(std::vector<glm::vec3>& verteces, size_t count)
{
	verteces_count = count;
	GLuint coords_vbo = 0;
	glGenBuffers(1, &coords_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, coords_vbo);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(glm::vec3), verteces.data(), GL_STATIC_DRAW);
	glBindVertexArray(vao);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
}

void Model::load_colors(GLfloat* colors, size_t count)
{

	GLuint colors_vbo = 0;
	glGenBuffers(1, &colors_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
	glBufferData(GL_ARRAY_BUFFER, 3 * count * sizeof(GLfloat), colors, GL_STATIC_DRAW);
	glBindVertexArray(vao);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);
}

void Model::load_normals(const std::vector < glm::vec3>& normals, size_t count)
{
	GLuint normals_vbo = 0;
	glGenBuffers(1, &normals_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, normals_vbo);
	glBufferData(GL_ARRAY_BUFFER, 3*3 * count * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);
	glBindVertexArray(vao);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(2);
}

void Model::load_indices(GLuint* indices, size_t count)
{
	indices_count = count;
	glBindVertexArray(vao);
	GLuint elementbuffer;
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof
	(GLuint), indices, GL_STATIC_DRAW);
}

void Model::load_shaders(const char* vect, const char* frag)
{
	GLint result = GL_FALSE;
	int infoLogLength;
	shader_programme = glCreateProgram();
	string vstext = loadFile(vect);
	const char* vertex_shader = vstext.c_str();
	string fstext = loadFile(frag);
	const char* fragment_shader = fstext.c_str();
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0)
	{
		char* errorMessage = new char[infoLogLength + 1];
		glGetShaderInfoLog(vs, infoLogLength, NULL, errorMessage);
		std::cout << errorMessage;
		delete[] errorMessage;
	}
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0)
	{
		char* errorMessage = new char[infoLogLength + 1];
		glGetShaderInfoLog(fs, infoLogLength, NULL, errorMessage);
		std::cout << errorMessage;
		delete[] errorMessage;
	}
	glAttachShader(shader_programme, vs);
	glAttachShader(shader_programme, fs);
	glBindAttribLocation(shader_programme, 0, "vertex_position");
	glBindAttribLocation(shader_programme, 1, "vertex_colour");
	glLinkProgram(shader_programme);
}

void Model::load_textures(const std::vector<glm::vec2>& tex, size_t count)
{
	GLuint tex_vbo = 0;
	glGenBuffers(1, &tex_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, tex_vbo);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(glm::vec2), tex.data(), GL_STATIC_DRAW);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, tex_vbo);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(2);

}