#include <iostream>
#include <GL/glew.h>

#include "Display.h"
#include "main.h"

Display::Display(int width, int height, const std::string& title) {
	std::cout << "Constructing Display..." << std::endl;

	//Initialise SDL.
	std::cout << "Initialising SDL..." << std::endl;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		FailAndExit("SDL failed to initialize");
	}

	m_width = width;
	m_height = height;

	//Number of bits stored for each colour. (2^n). Use 8(256) for standard.
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	//Number of bits allocated per pixel. In this case we want 32, enough for all 4 declared above.
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

	//Sets a depth buffer so that there is no erronius pixel overlapping.
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

	//Enable double buffering.
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

	//Create the GL context.
	m_glContext = SDL_GL_CreateContext(m_window);


	//Initialise GLEW.
	std::cout << "Initialising GLEW..." << std::endl;
	GLenum status = glewInit();
	if (status != GLEW_OK) {
		std::cout << "GLEW Error: " << glewGetErrorString(status) << std::endl;
		std::cout << "Glew failed to initialize!" << std::endl;
		GLOBAL_shouldClose = true;
	}

	//Enalble the depth buffer.
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void Display::Clear(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


float Display::GetAspectRatio() {
	return (float)m_width / (float)m_height;
}

void Display::Update() {
	SDL_GL_SwapWindow(m_window);
}

Display::~Display() {
	std::cout << "Destructing Display..." << std::endl;

	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
}