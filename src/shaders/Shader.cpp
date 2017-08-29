#include "Shader.h"
#include <iostream>
#include <fstream>

#include "../util/Util.h"

const static string   VERTEX_EXTENSION = ".v.glsl";
const static string FRAGMENT_EXTENSION = ".f.glsl";

static std::string LoadShader(const std::string& fileName);
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static GLuint CreateShader(const std::string&& text, GLenum shaderType);

Shader::Shader(std::string fileName)
{
	std::cout << "Creating shader... '" << fileName << "'" << std::endl;

	m_name = fileName;

	//Creates some space on the GPU for a program.
	program = glCreateProgram();

	shaders[VERTEX] = CreateShader(LoadShader(fileName + VERTEX_EXTENSION), GL_VERTEX_SHADER);
	shaders[FRAGMENT] = CreateShader(LoadShader(fileName + FRAGMENT_EXTENSION), GL_FRAGMENT_SHADER);

	//Add the shaders to the program.
	for (unsigned int ii = 0; ii < NUM_SHADERS; ii++) {
		glAttachShader(program, shaders[ii]);
	}

	//Ensure 'position' is spelled the same as in the shader program itself.
    //These match up to the items defined in Mesh.cpp, each one is a VBO inside the VAO
	glBindAttribLocation(program, 0, "position");
	glBindAttribLocation(program, 1, "texCoord");
	glBindAttribLocation(program, 2, "normal");

	//Link the program.
	glLinkProgram(program);

	//Check for errors.
	CheckShaderError(program, GL_LINK_STATUS, true, "Error: Program failed to link: ");

	//Validate the program.
	glValidateProgram(program);

	//Check for errors.
	CheckShaderError(program, GL_VALIDATE_STATUS, true, "Error: Program is invalid: ");

	//Set our Uniform variables.
	uniforms[TRANSFORM_U] = glGetUniformLocation(program, "transform");
}


std::string Shader::GetName(){
	return m_name;
}

void Shader::Bind() {
	glUseProgram(program);
}

void Shader::Update(const Transform& transform, const Camera& camera) {
	//@Efficiency, calculating the model every update call when we can cache
	//this value per frame.
	glm::mat4 model = camera.GetViewProjection() * transform.GetModel();
	glUniformMatrix4fv(uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
}

Shader::~Shader()
{
	std::cout << "Destroying shader... '" << m_name << "'" << std::endl;

	for (int ii = 0; ii < NUM_SHADERS; ii++) {
		glDetachShader(program, shaders[ii]);
		glDeleteShader(shaders[ii]);
	}

	glDeleteProgram(program);
}

static GLuint CreateShader(const std::string&& text, GLenum shaderType) {
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0) {
		std::cout << "Error: Shader creation failed!" << std::endl;
	}

	const GLchar *shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];
	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringLengths[0] = text.length();

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed!");

	return shader;
}


static std::string LoadShader(const std::string& fileName) {
	std::ifstream file;

	file.open(fileName.c_str());

	std::string output;
	std::string line;

	if (file.is_open()) {
		while (file.good()) {
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else {
		std::cout << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage) {
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram) {
		glGetProgramiv(shader, flag, &success);
	}
	else {
		glGetShaderiv(shader, flag, &success);
	}

	if (success == GL_FALSE) {
		if (isProgram) {
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}
		else {
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}

		std::cout << errorMessage << " '" << error << "'" << std::endl;
	}
}
