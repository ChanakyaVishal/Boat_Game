#include "rock.h"
#include "main.h"

Rock::Rock(float x, float y,float z){
    this->position = glm::vec3(x, y, z);
    this->rotation = 90;
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
     for (int i=0 ;i<12*3*3;i++) cube[i] *= 4;

 this->object = create3DObject(GL_TRIANGLES, 12*3, cube, COLOR_ROCK, GL_FILL);
}


void Rock::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

bounding_box_t Rock::bounding_box() {
    float x = this->position.x, y = this->position.y, z = this->position.z;
    bounding_box_t bbox = { x,y, z, 4.5,4.5,4.5};
    return bbox;
}

