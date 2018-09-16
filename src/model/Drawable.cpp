#include "model/Drawable.h"


Drawable::Drawable(std::string name, float x_pos, float y_pos, Shader* shader)
                   : Entity(name, x_pos, y_pos)
{
    m_Shader = shader;

    // Create Vertex Array Object
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // Create a Vertex Buffer Object and copy the vertex data to it
    glGenBuffers(1, &m_vbo);

    GLfloat m_Vertices[] =
    {
        x_pos + -0.5f, y_pos + 0.5f,  1.0f, 0.0f, 0.0f, // Top-left
        x_pos + 0.5f,  y_pos + 0.5f,  0.0f, 1.0f, 0.0f, // Top-right
        x_pos + 0.5f,  y_pos + -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
        x_pos + -0.5f, y_pos + -0.5f, 0.0f, 0.0f, 0.0f, // Bottom-left
    };

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertices), m_Vertices, GL_STATIC_DRAW);


    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(m_Shader->GetProgram(), "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);

    // Get the location of the color uniform
    GLint colorAttrib = glGetAttribLocation(m_Shader->GetProgram(), "color");
    glEnableVertexAttribArray(colorAttrib);
    glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float),
                          (void*)(2*sizeof(GLfloat)));

    // A list of the elements in the above array.
    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0
    };

    //This may need to change, not too sure.
    m_Drawcount = sizeof(elements);

    //Load this element buffer object into grpahics memory.
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(elements), elements, GL_STATIC_DRAW);

}

void Drawable::Draw(){
    m_Shader->Bind();

    glBindVertexArray(m_vao);

    glDrawElements(GL_TRIANGLES, m_Drawcount, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

Drawable::~Drawable(){
    glDeleteVertexArrays(1, &m_vao);
    // Probably have to do more cleanup, vbo / ebo?
}
