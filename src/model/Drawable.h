#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <GL/glew.h>

#include "Entity.h"
#include "Shader.h"

class Drawable{
    public:
        Drawable(Shader* shader);

        void Draw();

        ~Drawable();

    private:
        Shader* m_Shader;
        GLuint m_vao;
        GLuint m_vbo;
};


#endif //DRAWABLE_H
