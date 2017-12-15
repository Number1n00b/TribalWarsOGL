#include <iostream>

#include "../main/main.h"
#include "resource_loader.h"

//================= Fonts =====================
void LoadFonts(unordered_map<string, Font*>* catalogue, string font_directory_path){
	FT_Library* ft_lib = new FT_Library();
	if(FT_Init_FreeType( ft_lib )){
		Game::FailAndExit("FreeType failed to initialize.");
	}

    CreateFont(ft_lib, font_directory_path + "/28_days_later.ttf", "28_days_later", catalogue);

	CreateFont(ft_lib, font_directory_path + "/open-sans/OpenSans-Regular.ttf", "OpenSans_Regular", catalogue);

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
void LoadShaders(unordered_map<string, Shader*>* catalogue, string shader_directory_path){
	//Primitive shapes
	CreateShader(shader_directory_path + "/primShader",  "primitives", catalogue);

	//Standard
    CreateShader(shader_directory_path + "/basicShader",  "standard",  catalogue);

	//Sphere. (Colourful)
    CreateShader(shader_directory_path + "/sphereShader", "sphere",    catalogue);

	//Text
    CreateShader(shader_directory_path + "/textShader",   "text",      catalogue);
}


void CreateShader(string filename, string name, unordered_map<string, Shader*>* catalogue){
	Shader *s = new Shader(filename);
	(*catalogue)[name] = s;
}
//=============== END Shaders ===================


//================= Meshes =====================
void LoadMeshes(unordered_map<string, Mesh*>* catalogue, string mesh_directory_path){
	CreateMesh(mesh_directory_path + "/monkey3.obj",   "monkey3",   catalogue);
	CreateMesh(mesh_directory_path + "/myCar.obj",     "my_car",    catalogue);
	CreateMesh(mesh_directory_path + "/6x6_plane.obj", "6x6_plane", catalogue);
	CreateMesh(mesh_directory_path + "/sphere.obj",    "sphere",    catalogue);
}

void CreateMesh(string filename, string name, unordered_map<string, Mesh*>* catalogue){
	Mesh *m = new Mesh(filename);
	(*catalogue)[name] = m;
}
//=============== END Meshes ===================


//================= Textures =====================
void LoadTextures(unordered_map<string, Texture*>* catalogue, string image_directory_path){
    CreateTexture(image_directory_path + "/bricks.jpg",  "bricks",  catalogue);
	CreateTexture(image_directory_path + "/sand.jpg",    "sand",    catalogue);

	CreateTexture(image_directory_path + "/x.jpg",       "x",       catalogue);
	CreateTexture(image_directory_path + "/y.jpg",       "y",       catalogue);
	CreateTexture(image_directory_path + "/z.jpg",       "z",       catalogue);
	CreateTexture(image_directory_path + "/blue.jpg",    "blue",    catalogue);
	CreateTexture(image_directory_path + "/my_grid.jpg", "my_grid", catalogue);
}

void CreateTexture(string filename, string name, unordered_map<string, Texture*>* catalogue){
	Texture *t = new Texture(filename);
	(*catalogue)[name] = t;
}
//=============== END Textures ===================
