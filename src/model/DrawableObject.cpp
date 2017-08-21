#include "DrawableObject.h"

bool DrawableObject::camera_set = false;
Camera* DrawableObject::s_camera = nullptr;

void DrawableObject::SetCamera(Camera *cam) {
    s_camera = cam;
    camera_set = true;
}

DrawableObject::DrawableObject(std::string name, Shader* shader, Texture *texture, Mesh *mesh, Transform transform)
    : WorldObject(name, shader, texture, mesh, transform)
{

}

void DrawableObject::Draw() {
    if (!camera_set) {
        std::cout << "!!!!!!!!!!! No camera set for Drawable class. !!!!!!!!!!!" << std::endl;
    }
    else {
        //@Speed, we shouldn't need to bind the shader every draw call, it most likely remains the same for multiple objects.
        m_shader->Bind();

        //@Speed, same for texture, multiple objects in a row could have the same texture. we should group objects with the same tecture to be drawn
        //        sequentually so that textures dont have to be swapped out as often.
        m_texture->Bind(0);

        //@Speed, the camera should remain unchanging between draw calls in a single frame, shader should not need to update it all the time.
        m_shader->Update(m_transform, *s_camera);

        //Draw the object's mesh.
        m_mesh->Draw();
    }
}


DrawableObject::~DrawableObject()
{
}
