#pragma once

#include <string>
#include <GL/glew.h>

#include "../model/Transform.h"

class Shader{
	public:
		Shader(std::string file_name);

		void Bind();
		void Update(const Transform& transform, const glm::mat4 view_projection);

		virtual ~Shader();

		std::string GetName();

	private:
		//One for vertex and one for fragment. (Could also have 'geometry shaders').
        enum shaders{
            VERTEX,
            FRAGMENT,

            NUM_SHADERS
        };

		//Just a way to refer to all our uniform variables for the shader.
		enum uniforms{
			TRANSFORM_U,

			NUM_UNIFORMS
		};

		std::string m_name;

		GLuint program;
		GLuint shaders[NUM_SHADERS];
		GLuint uniforms[NUM_UNIFORMS];
};
