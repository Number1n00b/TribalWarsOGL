#pragma once
#include <string>
#include <SDL.h>

class Display{
	public:
		Display(int width, int height, const std::string& title);

		void Clear(float r, float g, float b, float a);

		void Update();

		float GetAspectRatio();

        void UpdateViewport(int width, int height);

        SDL_Window* GetWindow();

		int GetWidth();
		int GetHeight();

		virtual ~Display();

	private:
		int m_width;
		int m_height;

		SDL_Window *m_window;
		SDL_GLContext m_GLContext;
};
