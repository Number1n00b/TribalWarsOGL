#pragma once

#include <string>
#include <GL/glew.h>

#include "Transform.h"
#include "Camera.h"

class Shader{

	public:
		Shader(const std::string& file_name);

		void Bind();
		void Update(const Transform& transform, const Camera& camera);

		virtual ~Shader();

	private:
		//One for vertex and one for fragment. (Could also have 'geometry shaders'). Should probably make this an enum to make referencing them explicit.
		static const unsigned int NUM_SHADERS = 2;

		//Just a way to refer to all our uniform variables for the shader.
		enum {
			TRANSFORM_U,

			NUM_UNIFORMS
		};

		GLuint m_program;
		GLuint m_shaders[NUM_SHADERS];
		GLuint m_uniforms[NUM_UNIFORMS];
};

