/*
TODO LIST:
NAMING CONVENTION:
Classes and Functions: FULL CamelCase
Variables/Parameters: under_scores
Class Member Variables: m_VariableName

1) User input.
    - Camera movement:
        Learn how 'look at' and 'up' correlate. Seems that those two vector must be perpendicular at all times. Learn how to update this.
    - Object movement:
        Enable object movement.

3) Main game loop.
    I want to update this so that it runs on a timer, being independant of CPU/GPU speeds.
    I want physics engine to run at 120 hz and framerate to be uncapped. (with max 120 i guess).

4) Rewrite what is not mine, or use free libaries (obj_loader and stb_image).

6) Find a way to initialise GLEW outside of Display.cpp so that if it fails we can close the program. (Do memory management too, deleting context etc).

7) Where possible: overload functions that take a single glm::vec3 to also be able to take 3 floats. (for convineince)

8) Find out how to draw UI elements. (Possible use a different shader).

9) Restructure main into an app class with all the variables required, use main to initialise and start the app class.

11) Make 'escape' toggle a pause menu, during the pause menu the mouse is NOT clipped to the screen. else it is.

NOTES:
To make the camera track an object, simply set its lookDirection to object.pos - cam.pos
*/

//Standard libs.
#include <iostream>


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

//Input
#include "InputEventHandler.h"

using std::cin;
using std::cout;
using std::endl;

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 800

std::vector<Drawable*> worldObjects;

int main(int argc, char *argv[]) {
	cout << "====== Starting Program... ======" << endl;

	//Craete the window and context.
	Display window(WINDOW_WIDTH, WINDOW_HEIGHT, "Main window.");

    InputEventHandler eventHandler = InputEventHandler();

    //Create the main camera.
    Camera mainCamera(glm::vec3(0, 5, 0), glm::vec3(0, -1, 0), glm::vec3(0, 0, 1), 70.0f, window.GetAspectRatio(), 0.01f, 1000.0f);

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
	while (!GLOBAL_shouldClose) {
        //Handle events first.
        eventHandler.HandleSDLEvents();

        //A random counter to make things change!
        counter += 0.02f;
        sinCounter = sinf(counter);
        cosCounter = cosf(counter);

        //Do physics updates
        //Make the transform change based on the counter.
        monkeyOneDrawable.GetTransform().SetPos(glm::vec3(2, 0, sinCounter));

        //Do the drawing
        Draw(window);
	}

	cout << "End of main loop." << endl;

	cout << "\nFreeing resources..." << endl;

	cout << "Deinitialising SDL..." << endl;
	SDL_Quit();

	cout << "====== Ending Program... ======" << endl;
	//cin.get();
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