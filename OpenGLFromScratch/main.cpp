/*
TODO LIST:
NAMING CONVENTION:
Classes and Functions: FULL CamelCase
Variables/Parameters: under_scores
Class Member Variables:
                    private: m_VariableName
                    public: variableName

1) User input.
    - Camera movement:
        Learn how 'look at' and 'up' correlate. Seems that those two vector must be perpendicular at all times. Learn how to update this.

4) Rewrite what is not mine, or use other, industry standard, free libaries (obj_loader and stb_image).

6) Find a way to initialise GLEW outside of Display.cpp so that if it fails we can close the program. (Do memory management too, deleting context etc).

8) Find out how to draw UI elements. (Possible use a different shader).

9) Restructure main into an app class with all the variables required, use main to initialise and start the app class. 

11) Make 'escape' toggle a pause menu, during the pause menu the mouse is NOT clipped to the screen. else it is.

12) Idk man... make the UI work with text. FreeType not working FeelsBadMan

13) Sound! :O

14) Framerate independant movement. (Change Update() to Update(timestep))

NOTES:
To make the camera track an object, simply set its lookDirection to object.pos - cam.pos
*/

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")

//Standard libs.
#include <iostream>
#include <windows.h>

//Graphics libs.
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_syswm.h>

#include "main.h"
int prev_cursor_X = 0;
int prev_cursor_Y = 0;

GAME_STATE game_state;

bool Game::ShouldClose = false;
int Window::Window_Width = 1080;
int Window::Window_Height = 800;


//Output
#include "Display.h"

//Model Classes
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"
#include "WorldObject.h"
#include "Player.h"
#include "UI.h"

//Input
#include "InputEventHandler.h"

using std::cin;
using std::cout;
using std::endl;

const int TARGET_FPS = 60;
const double ms_per_frame = 1000.0 / TARGET_FPS;

std::vector<WorldObject*> worldObjects;

Display *main_window;
Camera *main_camera;
InputEventHandler *eventHandler;

//UI *main_ui;

void Initialise() {
    //Craete the window and context.
    main_window = new Display(Window::Window_Width, Window::Window_Height, "Main window.");

    //Create the event handler.
    eventHandler = new InputEventHandler();

    //Create the main camera.
    main_camera = new Camera(glm::vec3(0, 5, 0), glm::vec3(0, -1, 0), glm::vec3(0, 0, 1), 70.0f, main_window->GetAspectRatio(), 0.01f, 1000.0f);

    //Initialise the UI
    //main_ui = new UI();

    //Set the camera for our drawable class as the main camera.
    WorldObject::SetCamera(main_camera);

    Game::ResumeGame();
}


int main(int argc, char *argv[]) {
	cout << "====== Starting Program... ======" << endl;

    //Initalise the basics, Camera, UI, window, eventhandler.
    Initialise();

    //Create the basic shaders.
    Shader shader("./res/basicShader");

    //Load our tectures.
    Texture piranahs("./res/download.jpg");
    Texture bricks("./res/bricks.jpg");

    //Load the game object meshes.
	Mesh monkeyMesh("./res/monkey3.obj");

    //Create our drawable game objects.
    WorldObject monkey_one("Monkey Number One", &shader, &bricks, &monkeyMesh);

    Player player_one("Monkey Number Two", &shader, &piranahs, &monkeyMesh, eventHandler);

    //Add the objects to the list of all objects.
    worldObjects.push_back(&monkey_one);
    worldObjects.push_back(&player_one);

	float counter = 0.0f;
	float sinCounter;
	float cosCounter;

    //Register global event listeners.
    eventHandler->RegisterMouseListener(main_camera);

	//The main loop!
	cout << "\nEntering main loop." << endl;

    double curr_time = 0;
    double prev_time = SDL_GetTicks();
    double dt = 0;

    double time_since_last_frame = 0;
    
    int num_frames = 0;
    int fps_timer_start = prev_time;
    int fps_timer_end;
	while (!Game::ShouldClose) {
        //Always handle events regardless of state.
        //Currently this works because WorldObjects only "Update" In the inner if statement: ie. when game is running. 
        //However, the event norifications are ALWAYS sent. So if somethign changes in the "NotifyEvent" method, it will change even in pause menu.
        eventHandler->HandleSDLEvents();

        //@TODO @Incomplete. Decide how to handle screen resize while paused. I think we should just draw one frame on resize to draw the entire window.
        //Like, dont even update, just draw the same frame again in the resized resolution. 
        if(game_state == RUNNING){
            curr_time = SDL_GetTicks();

            //dt here is time per loop
            dt = curr_time - prev_time;
            prev_time = curr_time;

            time_since_last_frame += dt;

            //Cap FPS and render only when needed.
            if (time_since_last_frame >= ms_per_frame) {
                num_frames++;
                if (num_frames == 100) {
                    fps_timer_end = curr_time;
                    cout << "FPS: " << (float(num_frames) / (float(fps_timer_end - fps_timer_start) / 1000.0)) << endl;
                    fps_timer_start = fps_timer_end;
                    num_frames = 0;
                }

                //Do physics updates
                //A random counter to make things change!
                counter += 0.02f;
                sinCounter = sinf(counter);
                cosCounter = cosf(counter);

                //Update all out objects.
                for (std::vector<WorldObject*>::iterator it = worldObjects.begin(); it != worldObjects.end(); it++) {
                    (*it)->Update();
                }

                //Make the transform change based on the counter.
                // MOVE ME SOMEWHERE ELSE ===================================================================
                // MOVE ME SOMEWHERE ELSE ===================================================================
                // MOVE ME SOMEWHERE ELSE ===================================================================
                // MOVE ME SOMEWHERE ELSE ===================================================================
                // MOVE ME SOMEWHERE ELSE ===================================================================
                monkey_one.GetTransform().SetPos(glm::vec3(2, 0, sinCounter));

                //main_camera->SetLookDirection(player_one.GetTransform().GetPos() - main_camera->GetPosition());

                //Render
                Window::Draw();

                time_since_last_frame = 0.0;
            }
        }
	}

    game_state = CLOSING;

	cout << "End of main loop." << endl;

	cout << "\nFreeing resources..." << endl;

	cout << "Deinitialising SDL..." << endl;
	SDL_Quit();

	cout << "====== Ending Program... ======" << endl;
	//cin.get();
	return 0;
}


void Window::ResizeWindow(int width, int height) {
    main_window->UpdateViewport(width, height);
    main_camera->SetAspectRatio(float(width) / float(height));

    Window::Window_Width = width;
    Window::Window_Height = height;
}

void Window::Draw() {
    //Clear the window.
    main_window->Clear(0.5, 0.5, 0.5, 0.5);

    //Draw our drawables.
    for (std::vector<WorldObject*>::iterator it = worldObjects.begin(); it != worldObjects.end(); it++) {
        (*it)->Draw();
    }

    //Swap buffers.
    main_window->Update();
}

void Game::FailAndExit(std::string message){
	cout << "\n======\nTHE PROGRAM HAS FAILED\n======\n" << message << endl;
	cin.get();
	exit(-1);
}

void Game::TogglePause() {
    if (game_state == PAUSED) {
        Game::ResumeGame();
    }
    else if (game_state == RUNNING) {
        Game::PauseGame();
    }
}

void Game::PauseGame() {
    game_state = PAUSED;

    //Let go of the cursor.
    SetCursorClip(false);
    SDL_ShowCursor(true);

    //Put the cursor back to where it was before we took control.
    //But first, ignore the mouse event generated.
    SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
    SDL_WarpMouseInWindow(NULL, prev_cursor_X, prev_cursor_Y);
    SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);
}

void Game::ResumeGame() {
    game_state = RUNNING;

    //Empty the event queue so that actions done while paused does not affect the game.
    SDL_PumpEvents();
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        //Do nothing.
    }
    //Grab the position of the mouse before we take over.
    SDL_GetMouseState(&prev_cursor_X, &prev_cursor_Y);

    //Grab the cursor.
    SetCursorClip(true);
    SDL_ShowCursor(false);
}


//@Robustness, this may have to be re-called every time the window is resized.
void Game::SetCursorClip(bool clip) {
    if (!clip) {
        //Unclip the cursor.
        ClipCursor(nullptr);
    }
    else {
        //Clip the cursor to the window. (Just incase. This isn't really needed since we're warping the mouse to center all the time.)
        SDL_SysWMinfo wmInfo;
        SDL_VERSION(&wmInfo.version);
        SDL_GetWindowWMInfo(main_window->GetWindow(), &wmInfo);
        HWND hwnd = wmInfo.info.win.window;

        RECT rect;
        GetClientRect(hwnd, &rect);

        POINT ul;
        ul.x = rect.left;
        ul.y = rect.top;

        POINT lr;
        lr.x = rect.right;
        lr.y = rect.bottom;

        MapWindowPoints(hwnd, nullptr, &ul, 1);
        MapWindowPoints(hwnd, nullptr, &lr, 1);

        rect.left = ul.x;
        rect.top = ul.y;

        rect.right = lr.x;
        rect.bottom = lr.y;

        ClipCursor(&rect);
    }
}
