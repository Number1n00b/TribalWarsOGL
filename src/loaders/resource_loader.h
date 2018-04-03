#ifndef RESOURCE_LOADER_H
#define RESOURCE_LOADER_H

//Standard libs
#include <string>
#include <unordered_map>

//Freetype Libraries
#include <ft2build.h>
#include FT_FREETYPE_H


//Resource types
#include "../model/Shader.h"
#include "../model/Mesh.h"
#include "../model/Texture.h"
#include "../model/Font.h"

//Using / Namespace declarations.
using std::string;
using std::unordered_map;

void LoadShaders(unordered_map<string, Shader*>* catalogue, string shader_directory_path);
void CreateShader(string filename, string name, unordered_map<string, Shader*>* catalogue);


void LoadMeshes(unordered_map<string, Mesh*>* catalogue, string mesh_directory_path);
void CreateMesh(string filename, string name, unordered_map<string, Mesh*>* catalogue);


void LoadTextures(unordered_map<string, Texture*>* catalogue, string texture_directory_path);
void CreateTexture(string filename, string name, unordered_map<string, Texture*>* catalogue);


void LoadFonts(unordered_map<string, Font*>* catalogue, string font_directory_path);
void CreateFont(FT_Library* ft_lib, string filename, string name, unordered_map<string, Font*>* catalogue);


#endif RESOURCE_LOADER_H
