#include "WorldObject.h"


bool WorldObject::camera_set = false;
Camera* WorldObject::s_camera = nullptr;

void WorldObject::SetCamera(Camera *cam) {
    s_camera = cam;
    camera_set = true;
}


WorldObject::WorldObject(std::string name, Shader *shader, Texture *texture, Mesh *mesh, Transform transform) {
    this->name = name;
    m_shader = shader;
    m_texture = texture;
    m_mesh = mesh;
    m_transform = transform;
}


void WorldObject::Draw() {
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

void WorldObject::Update() {
    //Empty
}

WorldObject::~WorldObject() {
    //Empty
    //@Incomplete? Should i set all class member pointers to null? I dont think so, it should be done automatically.
}