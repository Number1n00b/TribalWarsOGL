#pragma once
#include <string>
#include <GL/glew.h>

class Texture
{
	public:
		Texture(const std::string& fileName);

		Texture(const std::string& name, GLint packingFormat,
				int width, int height, const GLvoid* data);

		void Bind(unsigned int uint);

		std::string GetName();

		~Texture();

	private:
		GLuint m_texture;

		std::string m_name;

		bool isCharacterTexture;
};
