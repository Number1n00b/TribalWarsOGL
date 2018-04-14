#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <SDL.h>

class Display{
	public:
		Display(int width, int height, const std::string& title);

		void Clear(float r, float g, float b, float a);

		void SwapBuffers();

		float GetAspectRatio();

        void UpdateViewport(int width, int height);

        SDL_Window* GetWindow();

		int GetWidth();
		int GetHeight();

		void ToggleVSync();
		void EnableVSync();
		void DisableVSync();


		virtual ~Display();

	private:
		int m_width;
		int m_height;

		bool m_vsync_enabled = true;

		SDL_Window *m_window;
		SDL_GLContext m_GLContext;
};

#endif //DISPLAY_H
