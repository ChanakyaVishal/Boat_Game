#include "booster.h"
#include "main.h"

Booster::Booster(float x,float y,float z)
{
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
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
    for(int i=0; i<12*3*3; i++){
        if(i%3 == 0) cube[i] *=0.5;
        if(i%3 == 1) cube[i] *=0.5;
        if(i%3 == 2) cube[i] *=1;
    }
 this->object = create3DObject(GL_TRIANGLES, 12*3, cube, COLOR_BOOSTER, GL_FILL);
}


void Booster::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

bounding_box_t Booster::bounding_box() {
    float x = this->position.x, y = this->position.y, z = this->position.z;
    bounding_box_t bbox = { x,y, z, 1,1,1};
        return bbox;
    }
