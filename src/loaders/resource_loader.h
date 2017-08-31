//Standard libs
#include <string.h>
#include <unordered_map>

//Freetype Libraries
#include <ft2build.h>
#include FT_FREETYPE_H


//Resource types
#include "../model/Shader.h"
#include "../model/Mesh.h"
#include "../model/Texture.h"

//Using / Namespace declarations.
using std::string;
using std::unordered_map;

void LoadShaders(unordered_map<string, Shader*>* catalogue);
void CreateShader(string filename, string name, unordered_map<string, Shader*>* catalogue);


void LoadMeshes(unordered_map<string, Mesh*>* catalogue);
void CreateMesh(string filename, string name, unordered_map<string, Mesh*>* catalogue);


void LoadTextures(unordered_map<string, Texture*>* catalogue);
void CreateTexture(string filename, string name, unordered_map<string, Texture*>* catalogue);


void LoadFonts(unordered_map<string, FT_Face*>* catalogue);
void CreateFont(FT_Library* ft_lib, string filename, string name, unordered_map<string, FT_Face*>* catalogue);
