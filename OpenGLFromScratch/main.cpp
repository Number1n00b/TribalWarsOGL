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

4) Rewrite what is not mine, or use free libaries (obj_loader and stb_image).

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
#include <time.h>
#include <windows.h>

//Graphics libs.
#include <GL/glew.h>
#include <SDL.h>

#include "main.h"
bool GLOBAL_shouldClose = false;

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

const int WINDOW_WIDTH = 1080;
const int WINDOW_HEIGHT = 800;

const int TARGET_FPS = 60;
const double ms_per_frame = 1000.0 / TARGET_FPS;

std::vector<WorldObject*> worldObjects;

Display *main_window;
Camera *main_camera;

int main(int argc, char *argv[]) {
	cout << "====== Starting Program... ======" << endl;

	//Craete the window and context.
	main_window = new Display(WINDOW_WIDTH, WINDOW_HEIGHT, "Main window.");

    InputEventHandler eventHandler = InputEventHandler();

    //Create the main camera.
    main_camera = new Camera(glm::vec3(0, 5, 0), glm::vec3(0, -1, 0), glm::vec3(0, 0, 1), 70.0f, main_window->GetAspectRatio(), 0.01f, 1000.0f);

    //Initialise the UI
    //UI main_ui = UI();

    //Set the camera for our drawable class as the main camera.
    WorldObject::SetCamera(main_camera);

    //Create the basic shaders.
    Shader shader("./res/basicShader");

    //Load our tectures.
    Texture piranahs("./res/download.jpg");
    Texture bricks("./res/download.jpg");

    //Load the game object meshes.
	Mesh monkeyMesh("./res/monkey3.obj");

	Transform origin_transform;

    //Create our drawable game objects.
    WorldObject monkey_one("Monkey Number One", &shader, &piranahs, &monkeyMesh);

    Player player_one("Monkey Number Two", &shader, &bricks, &monkeyMesh, &eventHandler, origin_transform);
    worldObjects.push_back(&monkey_one);
    worldObjects.push_back(&player_one);

	float counter = 0.0f;
	float sinCounter;
	float cosCounter;

    //Register global event listeners.
    eventHandler.RegisterMouseListener(main_camera);
    eventHandler.RegisterKeyboardListener(main_window);

	//The main loop!
	cout << "\nEntering main loop." << endl;

    double curr_time = 0;
    double prev_time = timeGetTime();
    double dt = 0;

    double time_since_last_frame = 0;

	while (!GLOBAL_shouldClose) {
        //Handle events first.
        eventHandler.HandleSDLEvents();

        curr_time = timeGetTime();

        //dt here is time per loop
        dt = curr_time - prev_time;
        prev_time = curr_time;

        time_since_last_frame += dt;

        //Cap FPS and render only when needed.
        if (time_since_last_frame >= ms_per_frame) {
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

            //Render
            Draw();

            time_since_last_frame = 0.0;
        }
	}

	cout << "End of main loop." << endl;

	cout << "\nFreeing resources..." << endl;

	cout << "Deinitialising SDL..." << endl;
	SDL_Quit();

	cout << "====== Ending Program... ======" << endl;
	//cin.get();
	return 0;
}


Display* GetMainWindow() {
    return main_window;
}

Camera* GetMainCamera() {
    return main_camera;
}

void Draw() {
    //Clear the window.
    main_window->Clear(0.5, 0.5, 0.5, 0.5);

    //Draw our drawables.
    for (std::vector<WorldObject*>::iterator it = worldObjects.begin(); it != worldObjects.end(); it++) {
        (*it)->Draw();
    }

    //Swap buffers.
    main_window->SwapBuffers();
}

void FailAndExit(std::string message){
	cout << "\n======\nTHE PROGRAM HAS FAILED\n======\n" << message << endl;
	cin.get();
	exit(-1);
}