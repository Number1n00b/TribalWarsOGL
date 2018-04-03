#include <iostream>
#include <windows.h>

#include <GL/glew.h>
#include <SDL_syswm.h>

#include "Display.h"

Display::Display(int width, int height, const std::string& title) {
	std::cout << "Constructing Display..." << std::endl;

	m_width = width;
	m_height = height;

    //Number of bits stored for each colour. (2^n). Use 8(256) for standard.
    int colour_size = 8;
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, colour_size);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, colour_size);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, colour_size);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, colour_size);

	//Number of bits allocated per pixel. In this case we want 4*colour_zie, enough for all 4 declared above.
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, colour_size * 4);

	//Sets a depth buffer so that there is no erronious pixel overlapping.
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

	//Enable double buffering.
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
	 						    m_width, m_height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    SDL_SetWindowMinimumSize(m_window, 800, 600);
    SDL_SetWindowMaximumSize(m_window, 2560, 1600);

	//Create the GL context.
	m_GLContext = SDL_GL_CreateContext(m_window);
}

void Display::UpdateViewport(int width, int height) {
	m_width = width;
	m_height = height;
    glViewport(0, 0, width, height);
}


void Display::Clear(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


float Display::GetAspectRatio() {
	return (float)m_width / (float)m_height;
}

void Display::SwapBuffers() {
	//Swap buffers.
	SDL_GL_SwapWindow(m_window);
}

SDL_Window* Display::GetWindow() {
    return m_window;
}

int Display::GetWidth(){
	return m_width;
}

int Display::GetHeight(){
	return m_height;
}


Display::~Display() {
	std::cout << "Destructing Display..." << std::endl;

	SDL_GL_DeleteContext(m_GLContext);
	SDL_DestroyWindow(m_window);
}
