#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

//Freetype Libraries
#include <ft2build.h>
#include FT_FREETYPE_H

#include "Texture.h"

using std::string;
using std::unordered_map;

struct Character {
    Texture*   texture;    // ID handle of the glyph texture
    glm::ivec2 size;       // Size of glyph
    glm::ivec2 bearing;    // Offset from baseline to left/top of glyph
    GLuint     advance;    // Offset to advance to next glyph
};


class Font{
	public:
		Font(FT_Library* ft_lib, string filename, string name);

		~Font();

        string GetName();

        unordered_map<GLchar, Character> characters;

	private:
        void LoadCharacters(FT_Face* f);

        string name;
};
