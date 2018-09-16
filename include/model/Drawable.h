#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <GL/glew.h>

#include "model/Entity.h"
#include "model/Shader.h"

class Drawable : public Entity{
    public:
        Drawable(std::string name, float x_pos, float y_pos, Shader* shader);

        void Draw();

        ~Drawable();

    private:
        Shader* m_Shader;
        GLuint m_vao;
        GLuint m_vbo;

        //GLfloat* m_Vertices;
        int m_Drawcount;
};


#endif //DRAWABLE_H
