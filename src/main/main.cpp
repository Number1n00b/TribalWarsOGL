//Standard libs.
#include <iostream>
#include <windows.h> //For window events and manupulation. Also needed for glew.
#include <string>
#include <chrono>    //Timekeeping

//Graphics libs.
#include <GL/glew.h>

//Stops SDL from redefining main causing undefined reference to WinMain@16.
#define SDL_MAIN_HANDLED

//Libraries for mouse pointer manipulation.
#include <SDL.h>
#include <SDL_syswm.h>

//=== My headers ===
#include "main.h"

//Output
#include "../display/Display.h"

//Model Classes
#include "../model/Transform.h"
#include "../model/Camera.h"


//Using / Namespace declarations.
//IO
using std::cin;
using std::cout;
using std::endl;

//Types
using std::chrono::milliseconds;
using std::unordered_map;
using std::string;
using std::vector;
using glm::vec3;


//Game state variables.
GAME_STATE Game::curr_state;
bool Game::should_close = false;


/* ------ Statics ------ */

//Mouse position, used to capture and reset mouse on pause / unpause.
static int prev_cursor_X = 0;
static int prev_cursor_Y = 0;

//Window paramentrs.
static int window_width = 1080;
static int window_height = 800;

//FPS params. @TODO make these modifiable.
static const int TARGET_FPS = 60;
static const double MS_PER_FRAME = 1000.0 / TARGET_FPS;


void Initialis_Graphics(){
	//===============
    //     SDL
    //===============
	std::cout << "Initialising SDL..." << std::endl;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        Game::FailAndExit("SDL failed to initialize.");
	}

    //Note: A glContext must be created before initialising GLEW.
    //Therefore we have to create a Display first.
    //===============
    //     Display
    //===============
    //Craete the window and context.
    main_window = new Display(window_width, window_height, "Main window.");

    //===============
    //     GLEW
    //===============
    std::cout << "Initialising GLEW..." << std::endl;
    GLenum status = glewInit();
    if (status != GLEW_OK) {
        std::cout << "GLEW Error: " << glewGetErrorString(status) << std::endl;
        Game::FailAndExit("Glew failed to initialize.");
    }

    //Enalble the depth buffer.
    glEnable(GL_DEPTH_TEST);

    //Enable culling faces for proper depth handling.
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void Initialise_Game(){
    //Create the main camera.
    vec3 cam_position = vec3(0, 0, 0);
    vec3 cam_look_direction = vec3(0, 0, 1);
    vec3 cam_up_direaction = vec3(0, 1, 0);
    float cam_fov = 70;
    float cam_z_near = 0.01;
    float cam_z_far = 1000;
    main_camera = new Camera(cam_position, cam_look_direction, cam_up_direaction,
		 					 cam_fov, main_window->GetAspectRatio(),
							 cam_z_near, cam_z_far, window_width, window_height);

}


int main(int argc, char *argv[]) {
	cout << "------------------ Starting Program ------------------" << endl;

    //Initialise SDL, GLEW
	cout << "\n====== Initlialising Graphics ======" << endl;
    Initialise_Graphics();

    //Initalise the basics: Display and Camera
	cout << "\n====== Initlialising Game Elements. ======" << endl;
    Initialise_Game();

	cout << "------------------------------------------------------" << endl;


    //Main loop setup.
	cout << "\nEntering main loop." << endl;

    float curr_time = Get_Current_Time();
    float prev_time = curr_time;
    float dt = 0;

    //Start the game.
    Game::ResumeGame();

    //The main loop!
	while (!Game::should_close) {
        //@DEBUG
        GLenum err;
        while((err = glGetError()) != GL_NO_ERROR){
	        //Unfortunately getting the error string is not supported because we don't
            //have glu32.dll.
	        //const GLubyte* errorMessage = gluErrorString(err);
            cout << "\n+++++++++++ GL_Error: " << err << "++++++++++++++++\n";
		}

		/* Handle input events here. */

        curr_time = Get_Current_Time();

        //dt here is time since last frame.
        dt = curr_time - prev_time;
        prev_time = curr_time;


        //Cap FPS and render only when needed.
        if (dt >= MS_PER_FRAME) {

			//Update objects first.
			main_camera->Update(dt);

            //Render
            DrawFrame();

            dt = 0.0;
        }

    }

    Game::curr_state = CLOSING;

	cout << "End of main loop." << endl;

	cout << "\n====== Freeing Resources ======" << endl;
	delete main_window;
	delete main_camera;

	//Free SDL resources.
	cout << "Deinitialising SDL..." << endl;
	SDL_Quit();

	cout << "\n------------------ Ending Program ------------------" << endl;

    return EXIT_SUCCESS;
}


static void DrawFrame() {
    //Clear the window.
    main_window->Clear(0.5, 0.5, 0.5, 0.5);

    //Draw our drawables.
	/* @TODO draw shit */

    //Swap buffers.
    main_window->SwapBuffers();
}


/* === Below are administrative events and actions === */

void Game::FailAndExit(std::string error_message){
	cout << "\n++++++\nTHE PROGRAM HAS FAILED\n++++++\n" << message << endl;
	//cin.get();
	exit(EXIT_FAILURE);
}


static float Get_Current_Time(){
	return std::chrono::duration_cast<float>(system_clock::now().time_since_epoch());
}


static void ToggleWireframes(){
	static bool wireframes = false;

	wireframes = !wireframes;

	if (wireframes) {
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);
	}
	else{
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);
	}
}


static void ResizeWindow(int width, int height) {
	window_width = width;
	window_height = height;
    main_window->UpdateViewport(window_width, window_height);
    main_camera->NotifyScreenResize(window_width, window_height);
}


static void WarpMouse(float x = -1, float y = -1){
	//By default, warp the mouse to the center of the screen.
	if (x < 0) { x = main_window->GetWidth() / 2 }
	if (y < 0) { y = main_window->GetHeight() / 2 }

	SDL_WarpMouseInWindow(NULL, x, y);

	//Ignore the mouse movement event generated by warping the mouse.
	SDL_PumpEvents();
	SDL_FlushEvent(SDL_MOUSEMOTION);
}


//Clip or unclip the cursor to the window.
static void SetCursorClip(bool clip) {
    if (!clip) {
        //Unclip the cursor.
        ClipCursor(nullptr);

		return;
    }

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


static void TogglePause() {
    if (Game::curr_state == PAUSED) {
        Game::ResumeGame();
    }
    else if (Game::curr_state == RUNNING) {
        Game::PauseGame();
    }
}

static void PauseGame() {
    Game::curr_state = PAUSED;

    //Let go of the cursor.
    SetCursorClip(false);
    SDL_ShowCursor(true);

    //Put the cursor back to where it was before we took control.
    SDL_WarpMouseInWindow(NULL, prev_cursor_X, prev_cursor_Y);

    //Then ignore the mouse event generated.
    SDL_PumpEvents();
    SDL_FlushEvent(SDL_MOUSEMOTION);

    cout << "Pausing..." << endl;
}

static void ResumeGame() {
    Game::curr_state = RUNNING;

    //Empty the event queue so that actions done while paused does not affect the game.
    SDL_PumpEvents();
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        //Do nothing.
    }
    //Save the position of the mouse before we take over.
    SDL_GetMouseState(&prev_cursor_X, &prev_cursor_Y);

    //Grab the cursor.
    SetCursorClip(true);
    SDL_ShowCursor(false);

    cout << "Resuming... " << endl;
}
