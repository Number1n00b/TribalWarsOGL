#include <iostream>
#include <vector>
#include <assert.h>

#include "Texture.h"
#include "../loaders/stb_image.h"


Texture::Texture(const std::string& fileName){
	std::cout << "Loading texture: \"" << fileName << "\"" << std::endl;
	isCharacterTexture = false;
	m_name = fileName;

	int width, height, numComponents;

	unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);

	if (imageData == NULL) {
		std::cout << "Texture loading failed for texture: '" << fileName << "'!\n";
	}

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

    //Where 'S' and 'T' are coordinates like x and y, so we are setting the two axis' wrapping perameters.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	stbi_image_free(imageData);
}


//Create a texture for a font.
Texture::Texture(const std::string& name, GLint packingFormat,
				 int width, int height, const GLvoid* data)
 {
	m_name = name;
	isCharacterTexture = true;

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexImage2D(GL_TEXTURE_2D,
		         0,
				 packingFormat,
				 width,
				 height,
				 0,
				 packingFormat,
				 GL_UNSIGNED_BYTE,
				 data);

    //Where 'S' and 'T' are coordinates like x and y, so we are setting the two axis' wrapping perameters.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


//uint should just be 0 for most cases to the best of my knowledge.
void Texture::Bind(unsigned int uint) {
	assert(uint >= 0 && uint <= 31);

	//@TODO @Hardcoded. Figure out how to set active tecture to the one I want.
	//I dont fully remember what this is, or how to use it.
	glActiveTexture(GL_TEXTURE0 + uint);

	glBindTexture(GL_TEXTURE_2D, m_texture);
}

std::string Texture::GetName(){
	return m_name;
}

Texture::~Texture(){
	if(!isCharacterTexture){
		std::cout << "Destroying texture... '" << m_name << "'" << std::endl;
	}

	glDeleteTextures(1, &m_texture);
}
