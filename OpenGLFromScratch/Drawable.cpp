#include "Drawable.h"


bool Drawable::camera_set = false;
Camera* Drawable::s_camera = nullptr;

void Drawable::SetCamera(Camera *cam) {
    s_camera = cam;
    camera_set = true;
}


Drawable::Drawable(std::string name, Shader *shader, Texture *texture, Mesh *mesh, Transform transform) {
    this->name = name;
    m_shader = shader;
    m_texture = texture;
    m_mesh = mesh;
    m_transform = transform;
}


void Drawable::Draw() {
    if (!camera_set) {
        std::cout << "No camera set for Drawable class." << std::endl;
    }
    else {
        //@Speed, we shouldn't need to bind the shader every draw call, it most likely remains the same for multiple objects.
        m_shader->Bind();

        //@Speed, same for texture, multiple objects in a row could have the same texture. we should grou pobjects with the same tecture to be drawn
        //        sequentually so that textures dont have to be swapped out as often.
        m_texture->Bind(0);

        //@Speed, the camera should remain unchanging between draw calls in a single frame, shader should not need to update it all the time.
        m_shader->Update(m_transform, *s_camera);

        //Draw the object.
        m_mesh->Draw();
    }
}

void Drawable::Update() {
    //Empty.
}

Drawable::~Drawable() {
    //Empty
    //@Incomplete? Should i set all class member pointers to null? I dont think so, it should be done automatically.
}