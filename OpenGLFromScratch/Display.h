#pragma once
#include <string>
#include <SDL.h>

class Display{
	public:
		Display(int width, int height, const std::string& title);
		virtual ~Display();

		void Clear(float r, float g, float b, float a);

		void Update();

		float GetAspectRatio();
        
        void UpdateViewport(int width, int height);

        SDL_Window* GetWindow();

	private:
		int m_width;
		int m_height;

		SDL_Window *m_window;
		SDL_GLContext m_GLContext;
};