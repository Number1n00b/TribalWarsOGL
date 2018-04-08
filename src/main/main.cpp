//Standard libs.
#include <iostream>
#include <windows.h> //For window events and manupulation. Also needed for glew.
#include <string>
#include <chrono>    //Timekeeping
#include <stdio.h>

//Graphics libs. (Ensure this is included before any SDL files!)
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
#include "../model/Shader.h"

//Using / Namespace declarations.
//IO
using std::cin;
using std::cout;
using std::endl;

//Types
using std::chrono::milliseconds;
using std::string;
using glm::vec3;


//Game state variables.
GAME_STATE Game::curr_state;
bool Game::should_close = false;

//Global main camera
Camera* Game::main_camera;


/* ------ Statics ------ */

//The main game window.
static Display *main_window;

//Mouse position, used to capture and reset mouse on pause / unpause.
static int prev_cursor_X = 0;
static int prev_cursor_Y = 0;

//Window paramentrs.
static int window_width = 1080;
static int window_height = 800;

//FPS params. @TODO make these modifiable.
static const int TARGET_FPS = 2;
static const int MS_PER_FRAME = 1000.0 / TARGET_FPS;
static const float fps_smoothing = 0.3; // Favour newer values more.

// ------ Forward Declarations ------
//@Temporary to test stuff.
static void HandleSDLEvents();
void Game::FailAndExit(std::string error_message);
static float GetCurentTime_MS();
static void ToggleWireframes();

static void ResizeWindow(int width, int height);
static void WarpMouse(float x, float y);
static void SetCursorClip(bool clip);

static void TogglePause();
static void PauseGame();
static void ResumeGame();

//Declare Game::Time variables.
float Game::Time::curr_time_ms = 0;
float Game::Time::time_since_last_frame = 0;
float Game::Time::dt = 0;

void Initialise_Graphics(){
    //Note: A glContext must be created before initialising GLEW.
    //Therefore we have to create a Display first.
    //===============
    // Display + SDL
    //===============
    //Craete the window and context.
    main_window = new Display(window_width, window_height, "Main window.");

    //===============
    //     GLEW
    //===============
    std::cout << "Initialising GLEW..." << std::endl;
	glewExperimental = GL_TRUE;
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
    Game::main_camera = new Camera(cam_position, cam_look_direction, cam_up_direaction,
		 					 cam_fov, main_window->GetAspectRatio(),
							 cam_z_near, cam_z_far, window_width, window_height);

}





//@TEMP

// Shader sources
const GLchar* vertexSource = R"glsl(
    #version 150 core
    in vec2 position;
    void main()
    {
        gl_Position = vec4(position, 0.0, 1.0);
    }
)glsl";
const GLchar* fragmentSource = R"glsl(
    #version 150 core
    out vec4 outColor;
    void main()
    {
        outColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
)glsl";




int main(int argc, char *argv[]) {
	cout << "------------------ Starting Program ------------------" << endl;

    //Initialise SDL, GLEW
	cout << "\n======== Initlialising Graphics ==========" << endl;
    Initialise_Graphics();

    //Initalise the basics: Display and Camera
	cout << "\n====== Initlialising Game Elements =======" << endl;
    Initialise_Game();

	//Load resources: Shaders
	//cout << "\n============ Loading Shaders =============" << endl;
    //Load_Shaders();

	cout << "\n------------------------------------------------------" << endl;

    //Main loop setup.
	cout << "\nEntering main loop." << endl;

	//Declare Game::Time variables.
	Game::Time::curr_time_ms = GetCurentTime_MS();
	Game::Time::time_since_last_frame = 0;
	Game::Time::dt = 0;

	//prev_time_ms is the time at which the previous loop itteration ran.
	float prev_time_ms = Game::Time::curr_time_ms;

	float current_fps = 0;

    //Start the game.
    ResumeGame();

	//@DEBUG Just to see the cursor at game start and be able to exit.
	SetCursorClip(false);
	SDL_ShowCursor(true);

	//Use this namespace for greater clarity and ease of coding.
	using namespace Game::Time;

	/*@TEMP ============================================================= */
	// Create Vertex Array Object
	    GLuint vao;
	    glGenVertexArrays(1, &vao);
	    glBindVertexArray(vao);

	    // Create a Vertex Buffer Object and copy the vertex data to it
	    GLuint vbo;
	    glGenBuffers(1, &vbo);

	    GLfloat vertices[] = {
	         0.0f,  1.0f,
	         1.0f, -1.0f,
	        -1.0f, -1.0f
	    };

	    glBindBuffer(GL_ARRAY_BUFFER, vbo);
	    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	    // Create and compile the vertex shader
	    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	    glShaderSource(vertexShader, 1, &vertexSource, NULL);
	    glCompileShader(vertexShader);

	    // Create and compile the fragment shader
	    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	    glCompileShader(fragmentShader);

	    // Link the vertex and fragment shader into a shader program
	    GLuint shaderProgram = glCreateProgram();
	    glAttachShader(shaderProgram, vertexShader);
	    glAttachShader(shaderProgram, fragmentShader);
	    glBindFragDataLocation(shaderProgram, 0, "outColor");
	    glLinkProgram(shaderProgram);
	    glUseProgram(shaderProgram);

	    // Specify the layout of the vertex data
	    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	    glEnableVertexAttribArray(posAttrib);
	    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

		GLint status;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);

		if (status != GL_TRUE){
			printf("Status: %d\n", status);
		}else{
			printf("SUCESSS\n");
		}

	/*@TEMP ============================================================= */

    //The main loop!
	main_window->Clear(1.0, 0.0, 0.0, 1.0);
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
		HandleSDLEvents();

        curr_time_ms = GetCurentTime_MS();

        dt = curr_time_ms - prev_time_ms;
		prev_time_ms = curr_time_ms;

        time_since_last_frame += dt;

		//Update objects regardless of time passed. @TODO
		/* for all objects in {object list}: object.update(dt) */

		dt = 0;

        //Cap FPS and render only when needed.
        if (time_since_last_frame >= MS_PER_FRAME) {
			//Clear the current buffer.
			//main_window->Clear(0.0, 0.0, 0.0, 1.0);

			// Draw all objects.

			//Swap buffers.
			main_window->SwapBuffers();

			// Calculate fps value
			current_fps = (current_fps * fps_smoothing) + ( ((1 / time_since_last_frame) * 1000) * (1.0 - fps_smoothing) );
			printf("FPS (%f): %f\n", dt, current_fps);

			time_since_last_frame = 0;
        }

    }

    Game::curr_state = CLOSING;

	glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);

    glDeleteBuffers(1, &vbo);

    glDeleteVertexArrays(1, &vao);



	cout << "End of main loop." << endl;
	cout << "\n=========== Freeing Resources ============" << endl;
	delete main_window;
	delete Game::main_camera;

	//Free SDL resources.
	cout << "Deinitialising SDL..." << endl;
	SDL_Quit();

	cout << "\n------------------- Ending Program -------------------" << endl;

    return EXIT_SUCCESS;
}


//@TODO later move this into an input file
static void HandleSDLEvents(){
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            //Handle special quit event,
            case SDL_QUIT:
            {
                Game::should_close = true;
                break;
            }

            //Handle resize events.
            case SDL_WINDOWEVENT:
            {
                if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
                    ResizeWindow(e.window.data1, e.window.data2);
                }
                break;
            }

			//Handle any key press.
            case SDL_KEYDOWN: case SDL_KEYUP: case SDL_TEXTINPUT:
            {
				//@TODO later abstract this into listeners, with UI listening for esacpe key
				// HandleKeyPress(e.key.keysym.sym);

                //Handle special button events. (Escape)
                //Ensure only to handle special events on KeyDown.
                if(e.type == SDL_KEYDOWN){
                    switch (e.key.keysym.sym) {
                        //Pause event. RGUI and LGUI are the windows keys.
                        case SDLK_ESCAPE: case SDLK_RGUI: case SDLK_LGUI:
                        {
                            TogglePause();
                            break;
                        }
                    }
                 }
                break;
            }

            case SDL_MOUSEMOTION: case SDL_MOUSEWHEEL: case SDL_MOUSEBUTTONDOWN: case SDL_MOUSEBUTTONUP:
            {
				//NotifyMouseListeners(e);
                break;
            }

            //Common events I am unsure of.
            case 770:
            {
                //Do nothing.
                break;
            }

            default:
            {
                cout << "Unknown event: " << e.type << endl;
                break;
            }
        }
    }
}


/* === Below are administrative events and actions === */

void Game::FailAndExit(std::string error_message){
	cout << "\n++++++\nTHE PROGRAM HAS FAILED\n++++++\n" << error_message << endl;
	//cin.get();
	exit(EXIT_FAILURE);
}


//Returns the time in milliseconds since the program launched.
static float GetCurentTime_MS(){
	static auto launch_time = std::chrono::high_resolution_clock::now();

	std::chrono::duration<float> curr = std::chrono::high_resolution_clock::now() - launch_time;

	return curr.count() * 1000;
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
    Game::main_camera->NotifyScreenResize(window_width, window_height);
}


static void WarpMouse(float x = -1, float y = -1){
	//By default, warp the mouse to the center of the screen.
	if (x < 0) { x = main_window->GetWidth() / 2; }
	if (y < 0) { y = main_window->GetHeight() / 2; }

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
        ResumeGame();
    }
    else if (Game::curr_state == RUNNING) {
        PauseGame();
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
