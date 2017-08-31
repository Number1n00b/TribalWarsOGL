#include "UI.h"

UI::UI(Shader* textShader, float screen_width, float screen_height){
    this->textShader = textShader;

    //Set up the projection matrix based on the screen size.
    m_projection = glm::ortho(0.0f, screen_width, 0.0f, screen_height);

    //Set up the memory that will contain text information.
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void UI::RenderText(Font* font, string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color){
    //Enable blend for text.
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Activate corresponding render state
    textShader->Bind();
    glUniform3f(glGetUniformLocation(textShader->GetProgram(), "textColor"), color.x, color.y, color.z);
    glUniformMatrix4fv(glGetUniformLocation(textShader->GetProgram(), "projection"), 1, GL_FALSE, (GLfloat*)&m_projection);

    glBindVertexArray(m_VAO);

    // Iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = font->characters[*c];

        GLfloat xpos = x + ch.bearing.x * scale;
        GLfloat ypos = y - (ch.size.y - ch.bearing.y) * scale;

        GLfloat w = ch.size.x * scale;
        GLfloat h = ch.size.y * scale;
        // Update VBO for each character
        GLfloat vertices[6][4] = {
            { xpos,     ypos + h,   0.0, 0.0 },
            { xpos,     ypos,       0.0, 1.0 },
            { xpos + w, ypos,       1.0, 1.0 },

            { xpos,     ypos + h,   0.0, 0.0 },
            { xpos + w, ypos,       1.0, 1.0 },
            { xpos + w, ypos + h,   1.0, 0.0 }
        };

        // Render glyph texture over quad
        ch.texture->Bind(0);

        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    //Disable blend.
    glDisable(GL_BLEND);
}


void UI::UpdateWindowSize(float width, float height){
    //Create a new projection based on new size.
    m_projection = glm::ortho(0.0f, width, 0.0f, height);
}


UI::~UI(){
    std::cout << "Destroying UI...\n";

    //Destroy the VAO
	glDeleteVertexArrays(1, &m_VAO);
}
