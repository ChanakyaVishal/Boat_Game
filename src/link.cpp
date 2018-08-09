#include "link.h"
#include "main.h"

Link::Link(float x, float y,float z)
{
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->starting_point_x = x;
    this->starting_point_z = z;
    this->dir_flag = 1;
    GLfloat cube[] = {
               -1.0f,-1.0f,-1.0f,
               -1.0f,-1.0f, 1.0f,
               -1.0f, 1.0f, 1.0f,
                           1.0f, 1.0f,-1.0f,
                           -1.0f,-1.0f,-1.0f,
                           -1.0f, 1.0f,-1.0f,
               1.0f,-1.0f, 1.0f,
               -1.0f,-1.0f,-1.0f,
               1.0f,-1.0f,-1.0f,
                               1.0f, 1.0f,-1.0f,
                               1.0f,-1.0f,-1.0f,
                               -1.0f,-1.0f,-1.0f,
               -1.0f,-1.0f,-1.0f,
               -1.0f, 1.0f, 1.0f,
               -1.0f, 1.0f,-1.0f,
                               1.0f,-1.0f, 1.0f,
                               -1.0f,-1.0f, 1.0f,
                               -1.0f,-1.0f,-1.0f,
               -1.0f, 1.0f, 1.0f,
               -1.0f,-1.0f, 1.0f,
               1.0f,-1.0f, 1.0f,
                               1.0f, 1.0f, 1.0f,
                               1.0f,-1.0f,-1.0f,
                               1.0f, 1.0f,-1.0f,
               1.0f,-1.0f,-1.0f,
               1.0f, 1.0f, 1.0f,
               1.0f,-1.0f, 1.0f,
                               1.0f, 1.0f, 1.0f,
                               1.0f, 1.0f,-1.0f,
                               -1.0f, 1.0f,-1.0f,
               1.0f, 1.0f, 1.0f,
               -1.0f, 1.0f,-1.0f,
               -1.0f, 1.0f, 1.0f,
                               1.0f, 1.0f, 1.0f,
                               -1.0f, 1.0f, 1.0f,
                               1.0f,-1.0f, 1.0f
           };


 this->object = create3DObject(GL_TRIANGLES, 12*3, cube, COLOR_OCTOROK, GL_FILL);
}


void Link::tick() {
    this->direction = glm::vec3(-sin(this->rotation * M_PI / 180.0f), 0, -cos(this->rotation * M_PI / 180.0f));
    int boost = 1;
    this->speedx -= 0.1*this->speedx;
    this->speedz -= 0.1*this->speedz;

    this->position.x += this->speedx*boost;
    this->position.z += this->speedz*boost;

    if(this->flag_air == 1){
        this->speedy -= 0.1;
       if(this->position.y <= 0){
           this->position.y = 0;
           this->speedy = 0;
           this->flag_air = 0;
       }
       this->position.y += this->speedy;
    }

}


void Link::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

bounding_box_t Link::bounding_box() {
    float x = this->position.x, y = this->position.y, z = this->position.z;
    bounding_box_t bbox = { x,y, z, 10,10,10};
    return bbox;
}
