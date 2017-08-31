#include <iostream>

#include "Font.h"

Font::Font(FT_Library* ft_lib, string filename, string name){
    std::cout << "Loading font: \"" << filename << "\"" << std::endl;

    this->name = name;

    FT_Face* face = new FT_Face();
	if (FT_New_Face(*ft_lib, filename.c_str(), 0, face)){
		//We don't close the program here because we can use a standard font
		//if others failed to load.
		//@Robustness: Not sure if this is the best way to handle it, lets wait and see.
		std::cout << "\n+++++ WARNING +++++\nFailed to load font: '" << filename << "'\n\n";
	}else{
        LoadCharacters(face);
	}
}

Font::LoadCharacters(FT_Face* f){
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

    FT_Face face = *f;

    //Load the first 128 characters of the ascii table.
    for (GLubyte c = 0; c < 128; c++)
    {
        // Load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "\n+++++ WARNING +++++\nFailed to load glyph: "\
            << char(c) << "\n\n";
            continue;
        }

        //@TODO make this use my own texture class somhow?
        // Generate texture
        Texture* t = new Texture(name + "_" + char(c), GL_RED,
                                face->glyph->bitmap.width,
                                face->glyph->bitmap.rows,
                                face->glyph->bitmap.buffer
                                );

        // Now store character for later use
        Character character = {
            t,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<GLuint>(face->glyph->advance.x)
        };
        characters.insert(std::pair<GLchar, Character>(c, character));
    }

    //Free resources.
    FT_Done_Face(face);
}


string Font::GetName(){
    return name;
}


Font::~Font(){
    std::cout << "Destroying font... '" << name << "'\n";

    //Delete the tecture for each character.
    for( const auto& n : characters ) {
		delete(n.second.texture);
	}
}
