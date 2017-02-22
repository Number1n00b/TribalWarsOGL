#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "obj_loader.h"

#include "Vertex.h"

class Mesh {
	public:
		Mesh(Vertex *vertices, unsigned int num_vertices, unsigned int *indicies, unsigned int num_indicies);
		Mesh(const std::string& file_name);

		void Draw();

		virtual ~Mesh();

	private:
		void InitMesh(const IndexedModel& model);

		//Enum to keep track of vertex buffer objects.
		enum {
			POSITION_VB,
			TEXCOORD_VB,
			NORMAL_VB,

			INDEX_VB,

			NUM_BUFFERS
		};

		GLuint m_vertexArrayObject;
		GLuint m_vertexArrayBuffers[NUM_BUFFERS];

		//How much of the vertexArrayObject we want to draw.
		unsigned int m_drawCount;
};

