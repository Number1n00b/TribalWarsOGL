#include "Drawable.h"


Drawable::Drawable(Shader* shader){
    m_Shader = shader;

    // Create Vertex Array Object
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // Create a Vertex Buffer Object and copy the vertex data to it
    GLuint m_vbo;
    glGenBuffers(1, &m_vbo);

    GLfloat vertices[] = {
        -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // Top-left
        0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Top-right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // Bottom-left
    };

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


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

    //Load this element buffer object into grpahics memory.
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(elements), elements, GL_STATIC_DRAW);

}

void Drawable::Draw(){
    m_Shader->Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

Drawable::~Drawable(){
    // Empty
}
