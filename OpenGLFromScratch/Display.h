#pragma once
#include <string>
#include <SDL.h>

#include "KeyboardListener.h"

class Display : public KeyboardListener{
	public:
		Display(int width, int height, const std::string& title);
		virtual ~Display();

		void Clear(float r, float g, float b, float a);

		void Update();

		float GetAspectRatio();
        
        void UpdateViewport(int width, int height);

        void SetMouseControl(bool clip);

        void NotifyKeyEvent(SDL_Event e);

	private:
		int m_width;
		int m_height;

        bool m_ControlMouse;

        int m_PrevMousePositionX;
        int m_PrevMousePositionY;

		SDL_Window *m_window;
		SDL_GLContext m_glContext;
};