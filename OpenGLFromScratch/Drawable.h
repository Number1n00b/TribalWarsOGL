#pragma once
#include <glm/glm.hpp>
#include <iostream>

#include "Transform.h"
#include "Texture.h"
#include "Mesh.h"
#include "Camera.h"
#include "Shader.h"

//Anything that could appear on screen should inherit from this class.
class Drawable
{
    public:
	    Drawable(std::string name, Shader *shader, Texture *texture, Mesh *mesh, Transform transform = Transform());

        virtual void Draw();

	    virtual ~Drawable();

        //The name of the object, means nothing but is useful for debugging.
        std::string name;

        Transform& GetTransform() {
            return m_transform;
        }

        //The camera input is to extract how the object should be drawn; from which perspective, and should be the same for all drawable objects.
        static Camera *s_camera;

        static void SetCamera(Camera* cam);

    protected:
        //Flag to ensure camera is always set.
        static bool camera_set;

        //Orientation in worldspace.
        Transform m_transform;

        //The shader to use when drawing this object.
        Shader *m_shader;

        //Which texture the object should be drawn with.
        Texture *m_texture;

        //The mesh of the object which will be drawn.
        Mesh *m_mesh;
};

