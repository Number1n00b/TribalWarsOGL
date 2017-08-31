//Standard libs.
#include <iostream>
#include <windows.h> //For window events and manupulation. Also needed for glew.
#include <string>

//Graphics libs.
#include <GL/glew.h>

//Stops SDL from redefining main causing undefined reference to WinMain@16.
#define SDL_MAIN_HANDLED

//Libraries for mouse pointer manipulation.
#include <SDL.h>
#include <SDL_syswm.h>

//=== My headers ===
#include "main.h"

//Loaders
#include "../loaders/resource_loader.h"

//Output
#include "../display/Display.h"
#include "../display/UI.h"

//Shaders
#include "../model/Shader.h"

//Model Classes
#include "../model/Mesh.h"
#include "../model/Transform.h"
#include "../model/Texture.h"
#include "../model/Camera.h"
#include "../model/WorldObject.h"
#include "../model/Player.h"
#include "../model/StaticObject.h"
#include "../model/Font.h"

//Input
#include "../input/InputEventHandler.h"

//Using / Namespace declarations.
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::unordered_map;
using std::vector;
using glm::vec3;


//Mouse position, used to capture and reset mouse on pause / unpause.
int prev_cursor_X = 0;
int prev_cursor_Y = 0;

//Game state variables.
GAME_STATE game_state;
bool Game::should_close = false;

//Window paramentrs.
static int window_width = 1080;
static int window_height = 800;

//FPS params.
const int TARGET_FPS = 60;
const double MS_PER_FRAME = 1000.0 / TARGET_FPS;

//Container for all objects in the world, Iterated over every Update() call.
vector<WorldObject*> world_objects;

//Globals for display, camera and events.
Display *main_window;
Camera *main_camera;
InputEventHandler *event_handler;
UI *main_ui;

//Dictionary of all textures.
static unordered_map<string, Texture*>* texture_catalogue;

//Dictionary of all meshes.
static unordered_map<string, Mesh*>* mesh_catalogue;

//Dictionary of all shaders.
static unordered_map<string, Shader*>* shader_catalogue;

//Dictionary of all fonts.
static unordered_map<string, Font*>* font_catalogue;

static float curr_fps = 0;

void Initialise_Graphics(){
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


    //Use this to draw wireframes.
    //glPolygonMode(GL_FRONT, GL_LINE);
}

void Initialise_Game(){
    //Create the event handler.
    event_handler = new InputEventHandler();

    //Create the main camera.
    vec3 cam_position = vec3(0, 0, 10);
    vec3 cam_look_direction = vec3(0, 0, -1);
    vec3 cam_up_direaction = vec3(0, 1, 0);
    float cam_fov = 70;
    float cam_z_near = 0.01;
    float cam_z_far = 1000;
    main_camera = new Camera(cam_position, cam_look_direction, cam_up_direaction,
		 					 cam_fov, main_window->GetAspectRatio(),
							 cam_z_near, cam_z_far, window_width, window_height);

    //Register global event listeners.
    event_handler->RegisterMouseListener(main_camera);
    event_handler->RegisterKeyboardListener(main_camera);

    //Set the camera for our drawable class as the main camera.
    WorldObject::SetCamera(main_camera);

	//Set up the asset catalogues.
	//Shader
	shader_catalogue = new unordered_map<string, Shader*>();

	//Mesh
	mesh_catalogue = new unordered_map<string, Mesh*>();

	//Texture
	texture_catalogue = new unordered_map<string, Texture*>();

	//Font
	font_catalogue = new unordered_map<string, Font*>();
}

void LoadResources(){
	LoadShaders(shader_catalogue);
	LoadMeshes(mesh_catalogue);
	LoadTextures(texture_catalogue);
	LoadFonts(font_catalogue);
}

void Initialise_UI(){
	//Create ui.
	main_ui = new UI((*shader_catalogue)["text"], window_width, window_height);
}


void CreateWorldObjects() {
    //Here we create all of the objects that start out in the world.
	//@TODO Have a list of startup objects and just iterate through it,
	//creating them all.

    //This transform ensures the monkeys face the right direction on spawn.
    Transform oriented_monkey;
    oriented_monkey.SetPos(0, 0, 20);
    oriented_monkey.SetRotation(0, 3.14, 0);

    //Create our drawable game objects.
    vec3 x_axis = vec3(1, 0, 0);
    vec3 y_axis = vec3(0, 1, 0);
    vec3 z_axis = vec3(0, 0, 1);
    float speed = 3;
    float amplitude = 6;

    //Create a standing monkey.
    Transform still_pos;
    still_pos.SetPos(0, 0, 0);

    WorldObject* still_monkey = new StaticObject("Monkey",
											    (*shader_catalogue)["standard"],
	 									        (*texture_catalogue)["x"],
												(*mesh_catalogue)["monkey3"],
												still_pos);
    world_objects.push_back(still_monkey);


    //Create a car.
    Transform car_pos;
    car_pos.SetPos(-5, -1, -10);
    car_pos.SetRotation(0, 3.14/2, 0);
    WorldObject* car = new StaticObject("Car",
						 		      	(*shader_catalogue)["standard"],
 									    (*texture_catalogue)["blue"],
										(*mesh_catalogue)["my_car"],
										car_pos);
    world_objects.push_back(car);

    //Create a floor.
    Transform floor_pos;
    floor_pos.SetPos(0, -3, 0);
	WorldObject* floor_tile = new StaticObject("Floor",
										  (*shader_catalogue)["standard"],
										  (*texture_catalogue)["my_grid"],
										  (*mesh_catalogue)["6x6_plane"],
										  floor_pos);
    world_objects.push_back(floor_tile);


    //Create the player.
	Player* sphere = new Player("Player (Sphere)",
						 	  	(*shader_catalogue)["sphere"],
								(*texture_catalogue)["my_grid"],
								(*mesh_catalogue)["sphere"],
								still_pos,
							  	event_handler);
    world_objects.push_back(sphere);
}


int main(int argc, char *argv[]) {
	cout << "------------------ Starting Program ------------------" << endl;

    //Initialise SDL, GLEW and FreeType
	cout << "\n====== Initlialising Graphics ======" << endl;
    Initialise_Graphics();

    //Initalise the basics, Camera, UI, window, eventhandler.
	cout << "\n====== Initlialising Game Elements. ======" << endl;
    Initialise_Game();

	//Load all the resources: Fonts, Meshes, Textures and Shaders
	cout << "\n====== Loading Resources ======" << endl;
	LoadResources();

	//Initialise the UI.
	cout << "\n====== Initialising UI ======" << endl;
	Initialise_UI();

	cout << "\n====== Creating World Objects ======" << endl;
    //Create all the objects in the world.
    CreateWorldObjects();

    cout << "Created:\n";
    for (std::vector<WorldObject*>::iterator it = world_objects.begin(); it != world_objects.end(); it++) {
        cout << "\t" << (*it)->name << endl;
    }

	cout << "======================================" << endl;
    //Main loop setup.
	cout << "\nEntering main loop." << endl;

    double curr_time = 0;
    double prev_time = SDL_GetTicks();
    double dt = 0;

    double time_since_last_frame = 0;

    int num_frames = 0;
    int fps_timer_start = prev_time;
    int fps_timer_end;

    //Start the game.
    Game::ResumeGame();

    //The main loop!
	while (!Game::should_close) {
		//@DEBUG
		GLenum err;
		while((err = glGetError()) != GL_NO_ERROR)
		{
  			cout << "\n+++++++++++ GL_Error: " << err << "++++++++++++++++\n";
		}

        //Always handle events regardless of state.
        //Currently this works because WorldObjects only "Update" In the inner if statement: ie. when game is running.
        //However, the event norifications are ALWAYS sent. So if somethign changes in the "NotifyEvent" method, it will change even in pause menu.
        event_handler->HandleSDLEvents();

        curr_time = SDL_GetTicks();

        //dt here is time per loop
        dt = curr_time - prev_time;
        prev_time = curr_time;

        time_since_last_frame += dt;

        //Do physics updates
        if (game_state == RUNNING && dt != 0) {
            //Update all our objects.
            for (std::vector<WorldObject*>::iterator it = world_objects.begin(); it != world_objects.end(); it++) {
                (*it)->Update(dt);
            }

            //Update the main camera.
            main_camera->Update(dt);
        }

        //Cap FPS and render only when needed. @NOTE: Physics updates done only on every render call.
        if (time_since_last_frame >= MS_PER_FRAME) {
            num_frames++;

            //This is just to display FPS
            if (num_frames == 100) {
                fps_timer_end = curr_time;
				curr_fps = (float(num_frames) / (float(fps_timer_end - fps_timer_start) / 1000.0));
                fps_timer_start = fps_timer_end;
                num_frames = 0;
            }

            //Render
            Game::DrawFrame();

            time_since_last_frame = 0.0;
        }
	}

    game_state = CLOSING;

	cout << "End of main loop." << endl;

	cout << "\n====== Freeing Resources ======" << endl;
	delete main_window;
	delete main_camera;
	delete event_handler;

	//Free all world objects
	for (std::vector<WorldObject*>::iterator it = world_objects.begin(); it != world_objects.end(); it++) {
        delete *it;
    }

	//Free shaders, meshes, textures and fonts.
	for( const auto& n : *shader_catalogue ) {
		delete n.second ;
	}
	delete shader_catalogue;

	for( const auto& n : *mesh_catalogue ) {
		delete n.second;
	}
	delete mesh_catalogue;

	for( const auto& n : *texture_catalogue ) {
		delete n.second;
	}
	delete texture_catalogue;

	for( const auto& n : *font_catalogue ) {
		delete n.second;
	}
	delete font_catalogue;

	//Destroy the UI
	delete main_ui;

	//Free SDL resources.
	cout << "Deinitialising SDL..." << endl;
	SDL_Quit();

	cout << "\n------------------ Ending Program ------------------" << endl;

	return 0;
}


void Game::ResizeWindow(int width, int height) {
	window_width = width;
	window_height = height;
    main_window->UpdateViewport(window_width, window_height);
    main_camera->NotifyScreenResize(window_width, window_height);
	main_ui->UpdateWindowSize(window_width, window_height);
}

void Game::DrawFrame() {
    //Clear the window.
    main_window->Clear(0.5, 0.5, 0.5, 0.5);

    //Draw our drawables.
    for (std::vector<WorldObject*>::iterator it = world_objects.begin(); it != world_objects.end(); it++) {
        (*it)->Draw();
    }

	//Draw the UI
	main_ui->RenderText((*font_catalogue)["28_days_later"], "PogChamp!",
						25.0f, 25.0f, 1.0f, glm::vec3(0.0f, 0.8f, 0.8f));

	main_ui->RenderText((*font_catalogue)["OpenSans_Regular"], "FPS: " + float_to_string(curr_fps),
		window_width - 150, window_height - 40.0f, 0.6f, glm::vec3(0.5f, 0.8f, 0.2f));

    if (game_state == RUNNING) {
        //Warp the mouse to the center of the window.
        SDL_WarpMouseInWindow(NULL, main_window->GetWidth() / 2,
                                    main_window->GetHeight() / 2);

        //Ignore the mouse movement event generated by warping the mouse.
        SDL_PumpEvents();
        SDL_FlushEvent(SDL_MOUSEMOTION);
    }

    //Swap buffers.
    main_window->Update();
}

void Game::FailAndExit(std::string message){
	cout << "\n++++++\nTHE PROGRAM HAS FAILED\n++++++\n" << message << endl;
	//cin.get();
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
    SDL_WarpMouseInWindow(NULL, prev_cursor_X, prev_cursor_Y);

    //Then ignore the mouse event generated.
    SDL_PumpEvents();
    SDL_FlushEvent(SDL_MOUSEMOTION);

    cout << "Pausing..." << endl;
}

void Game::ResumeGame() {
    game_state = RUNNING;

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
