#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>

class Shader{
	public:
		Shader(std::string file_name);

		void Bind();

        std::string GetName();

        GLuint GetProgram();

        virtual ~Shader();

	private:
		//One for vertex and one for fragment. (Could also have 'geometry shaders').
        enum shaders{
            VERTEX,
            FRAGMENT,

            NUM_SHADERS
        };

		std::string m_Name;

		GLuint m_Program;
		GLuint m_Shaders[NUM_SHADERS];
};

#endif //SHADER_H
