#include <iostream>
#include <fstream>

#include "model/Shader.h"

const static std::string   VERTEX_EXTENSION = ".v.glsl";
const static std::string FRAGMENT_EXTENSION = ".f.glsl";

static std::string LoadShader(const std::string& fileName);
static GLuint CreateShader(const std::string& text, GLenum shaderType);
static void CheckShaderError(GLuint shader, GLuint flag, bool ism_Program, const std::string& errorMessage);

Shader::Shader(std::string fileName)
{
	std::cout << "Loading shader: \"" << fileName << "\"" << std::endl;

	m_Name = fileName;

	//Creates some space on the GPU for a m_Program.
	m_Program = glCreateProgram();

    //Create the m_Shaders from the loaded source code.
	m_Shaders[VERTEX] = CreateShader(LoadShader(fileName + VERTEX_EXTENSION), GL_VERTEX_SHADER);
	m_Shaders[FRAGMENT] = CreateShader(LoadShader(fileName + FRAGMENT_EXTENSION), GL_FRAGMENT_SHADER);

	//Add the m_Shaders to the m_Program.
	for (unsigned int ii = 0; ii < NUM_SHADERS; ii++) {
		glAttachShader(m_Program, m_Shaders[ii]);
	}

	//Ensure each variable here is spelled the same as in the shader m_Program itself.
    //@TODO @Robustness this will cause issues alter on when different shaders use different stuff.
	glBindAttribLocation(m_Program, 0, "position");

	//Link the m_Program.
	glLinkProgram(m_Program);

	//Check for errors.
	CheckShaderError(m_Program, GL_LINK_STATUS, true, "Error: m_Program failed to link: ");

	//Validate the m_Program.
	glValidateProgram(m_Program);

	//Check for errors.
	CheckShaderError(m_Program, GL_VALIDATE_STATUS, true, "Error: m_Program is invalid: ");
}


std::string Shader::GetName(){
	return m_Name;
}

GLuint Shader::GetProgram(){
	return m_Program;
}

void Shader::Bind() {
	glUseProgram(m_Program);
}


Shader::~Shader()
{
	std::cout << "Destroying shader... '" << m_Name << "'" << std::endl;

	for (int ii = 0; ii < NUM_SHADERS; ii++) {
		glDetachShader(m_Program, m_Shaders[ii]);
		glDeleteShader(m_Shaders[ii]);
	}

	glDeleteProgram(m_Program);
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


static GLuint CreateShader(const std::string& text, GLenum shaderType) {
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0) {
		std::cout << "Error: Shader creation failed!" << std::endl;
	}

	const GLchar *ShaderSourceStrings[1];
	GLint ShaderSourceStringLengths[1];
	ShaderSourceStrings[0] = text.c_str();
	ShaderSourceStringLengths[0] = text.length();

	glShaderSource(shader, 1, ShaderSourceStrings, ShaderSourceStringLengths);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed!");

	return shader;
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
