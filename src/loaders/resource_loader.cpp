#include <iostream>

#include "../main/main.h"
#include "resource_loader.h"

//@TODO @cleanup @robustness: Have these directories be relative and auto-find them
const static string shader_dir = "F:/Programming_Projects/CPP/TribalWarsOGL/res/shaders";
const static string image_dir  = "F:/Programming_Projects/CPP/TribalWarsOGL/res/images";
const static string mesh_dir   = "F:/Programming_Projects/CPP/TribalWarsOGL/res/meshes";
const static string font_dir   = "F:/Programming_Projects/CPP/TribalWarsOGL/res/fonts";

//================= Fonts =====================
void LoadFonts(unordered_map<string, Font*>* catalogue){
	FT_Library* ft_lib = new FT_Library();
	if(FT_Init_FreeType( ft_lib )){
		Game::FailAndExit("FreeType failed to initialize.");
	}

    CreateFont(ft_lib, font_dir + "/28_days_later.ttf", "28_days_later", catalogue);

	CreateFont(ft_lib, font_dir + "/open-sans/OpenSans-Regular.ttf", "OpenSans_Regular", catalogue);

	//Free resources.
	FT_Done_FreeType(*ft_lib);
	delete ft_lib;
}

void CreateFont(FT_Library* ft_lib, string filename, string name, unordered_map<string, Font*>* catalogue){
    Font* f = new Font(ft_lib, filename, name);
	(*catalogue)[name] = f;
}
//=============== END fonts ===================


//================= Shaders =====================
void LoadShaders(unordered_map<string, Shader*>* catalogue){
	//Standard
    CreateShader(shader_dir + "/basicShader",  "standard", catalogue);

	//Sphere. (Colourful)
    CreateShader(shader_dir + "/sphereShader", "sphere",   catalogue);

	//Text
    CreateShader(shader_dir + "/textShader",   "text",     catalogue);
}


void CreateShader(string filename, string name, unordered_map<string, Shader*>* catalogue){
	Shader *s = new Shader(filename);
	(*catalogue)[name] = s;
}
//=============== END Shaders ===================


//================= Meshes =====================
void LoadMeshes(unordered_map<string, Mesh*>* catalogue){
	CreateMesh(mesh_dir + "/monkey3.obj",   "monkey3",   catalogue);
	CreateMesh(mesh_dir + "/myCar.obj",     "my_car",    catalogue);
	CreateMesh(mesh_dir + "/6x6_plane.obj", "6x6_plane", catalogue);
	CreateMesh(mesh_dir + "/sphere.obj",    "sphere",    catalogue);
}

void CreateMesh(string filename, string name, unordered_map<string, Mesh*>* catalogue){
	Mesh *m = new Mesh(filename);
	(*catalogue)[name] = m;
}
//=============== END Meshes ===================


//================= Textures =====================
void LoadTextures(unordered_map<string, Texture*>* catalogue){
    CreateTexture(image_dir + "/bricks.jpg",  "bricks",  catalogue);
	CreateTexture(image_dir + "/sand.jpg",    "sand",    catalogue);

	CreateTexture(image_dir + "/x.jpg",       "x",       catalogue);
	CreateTexture(image_dir + "/y.jpg",       "y",       catalogue);
	CreateTexture(image_dir + "/z.jpg",       "z",       catalogue);
	CreateTexture(image_dir + "/blue.jpg",    "blue",    catalogue);
	CreateTexture(image_dir + "/my_grid.jpg", "my_grid", catalogue);
}

void CreateTexture(string filename, string name, unordered_map<string, Texture*>* catalogue){
	Texture *t = new Texture(filename);
	(*catalogue)[name] = t;
}
//=============== END Textures ===================
