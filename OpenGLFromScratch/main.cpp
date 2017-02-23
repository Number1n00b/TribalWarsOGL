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
    - Object movement:
        Enable object movement.

4) Rewrite what is not mine, or use free libaries (obj_loader and stb_image).

6) Find a way to initialise GLEW outside of Display.cpp so that if it fails we can close the program. (Do memory management too, deleting context etc).

8) Find out how to draw UI elements. (Possible use a different shader).

9) Restructure main into an app class with all the variables required, use main to initialise and start the app class. 

11) Make 'escape' toggle a pause menu, during the pause menu the mouse is NOT clipped to the screen. else it is.

12) Idk man... make the UI work with text. FreeType not working FeelsBadMan

NOTES:
To make the camera track an object, simply set its lookDirection to object.pos - cam.pos
*/

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
//#pragma comment(lib, "freetype.lib")

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
#include "Drawable.h"
#include "Player.h"
//#include "UI.h"

//Input
#include "InputEventHandler.h"

using std::cin;
using std::cout;
using std::endl;

const int WINDOW_WIDTH = 1080;
const int WINDOW_HEIGHT = 800;

const int TARGET_FPS = 60;
const double ms_per_frame = 1000.0 / TARGET_FPS;

std::vector<Drawable*> worldObjects;

int main(int argc, char *argv[]) {
	cout << "====== Starting Program... ======" << endl;

	//Craete the window and context.
	Display window(WINDOW_WIDTH, WINDOW_HEIGHT, "Main window.");

    InputEventHandler eventHandler = InputEventHandler();

    //Create the main camera.
    Camera mainCamera(glm::vec3(0, 5, 0), glm::vec3(0, -1, 0), glm::vec3(0, 0, 1), 70.0f, window.GetAspectRatio(), 0.01f, 1000.0f);

    //Initialise the UI
    //UI main_ui = UI();

    //Set the camera for our drawable class as the main camera.
    Drawable::SetCamera(&mainCamera);

    //Create the basic shaders.
    Shader shader("./res/basicShader");

    //Load our tectures.
    Texture piranahs("./res/download.jpg");
    Texture bricks("./res/bricks.jpg");

    //Load the game object meshes.
	Mesh monkeyMesh("./res/monkey3.obj");

	Transform origin_transform;
    origin_transform.SetScale(glm::vec3(0.5f, 0.5f, 0.5f));

    //Create our drawable game objects.
    Player monkeyOneDrawable("Monkey Number One", &shader, &piranahs, &monkeyMesh, &eventHandler);
    Drawable monkey_origin("Monkey Number Two", &shader, &bricks, &monkeyMesh, origin_transform);
    worldObjects.push_back(&monkeyOneDrawable);
    worldObjects.push_back(&monkey_origin);

    monkeyOneDrawable.GetTransform().SetPos(glm::vec3(-2, 0, 0));

	float counter = 0.0f;
	float sinCounter;
	float cosCounter;

    //Register global event listeners.
    eventHandler.RegisterMouseListener(&mainCamera);
    eventHandler.RegisterKeyboardListener(&window);

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

            //Make the transform change based on the counter.
            monkeyOneDrawable.GetTransform().SetPos(glm::vec3(2, 0, sinCounter));

            //Render
            Draw(window);

            /*float sx = 2.0 / WINDOW_HEIGHT;
            float sy = 2.0 / WINDOW_WIDTH;

            main_ui.render_text("The Quick Brown Fox Jumps Over The Lazy Dog",
                -1 + 8 * sx, 1 - 50 * sy, sx, sy);
            main_ui.render_text("The Misaligned Fox Jumps Over The Lazy Dog",
                -1 + 8.5 * sx, 1 - 100.5 * sy, sx, sy);*/

            //cout << "FPS: " << (double)(1000.0 / time_since_last_frame) << endl;

            time_since_last_frame = 0.0;
        }
	}

	cout << "End of main loop." << endl;

	cout << "\nFreeing resources..." << endl;

	cout << "Deinitialising SDL..." << endl;
	SDL_Quit();

	cout << "====== Ending Program... ======" << endl;
	cin.get();
	return 0;
}

void Draw(Display& window) {
    //Clear the window.
    //window.Clear(cosCounter * sinCounter, cosCounter, sinCounter * sinCounter, cosCounter);
    window.Clear(0.5, 0.5, 0.5, 0.5);

    //Draw our drawables.
    for (std::vector<Drawable*>::iterator it = worldObjects.begin(); it != worldObjects.end(); it++) {
        (*it)->Draw();
    }

    //Swap buffers.
    window.Update();
}

void FailAndExit(std::string message){
	cout << "\n======\nTHE PROGRAM HAS FAILED\n======\n" << message << endl;
	cin.get();
	exit(-1);
}