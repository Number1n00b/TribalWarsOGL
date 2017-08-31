#pragma once

#include <string>
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "../model/Shader.h"
#include "../model/Font.h"

using std::string;

class UI{
    public:
        UI(Shader* textShader, float screen_width, float screen_height);

        void RenderText(Font* font, string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);

        void UpdateWindowSize(float width, float height);

        ~UI();

    private:
        Shader* textShader;

        //Projection matrix to draw on screen.
        glm::mat4 m_projection;

        //VAO and VBO handles.
        GLuint m_VAO;
        GLuint m_VBO;

};
