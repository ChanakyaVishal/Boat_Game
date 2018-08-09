#include "island.h"
#include "main.h"

Island::Island(float x, float y,float z){
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
        if(i%3 == 0) cube[i] *=100;
        if(i%3 == 1) cube[i] *=1;
        if(i%3 == 2) cube[i] *=100;
    }

 this->object = create3DObject(GL_TRIANGLES, 12*3, cube, COLOR_GREEN, GL_FILL);
    for(int i=0; i<12*3*3; i++){
        if(i%3 == 0) cube[i] /=2;
        if(i%3 == 1) cube[i] *=100;
        if(i%3 == 2) cube[i] /=2;
    }
   this->object1 = create3DObject(GL_TRIANGLES, 12*3, cube, COLOR_ROCK, GL_FILL);
    for(int i=0; i<12*3*3; i++){
        if(i%3 == 0) cube[i] /=2;
        if(i%3 == 1) cube[i] *=3;
        if(i%3 == 2) cube[i] /=2;
    }

}

void Island::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    this->rotation = 90;
    translate = glm::translate (glm::vec3(0,0,0));    // glTranslatef
    rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 1, 0));
    Matrices.model *= (translate * rotate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    this->rotation = 0;
    draw3DObject(this->object1);
}

bounding_box_t Island::bounding_box() {
    float x = this->position.x, y = this->position.y, z = this->position.z;
    bounding_box_t bbox = { x,y, z, 202,10,202};
    return bbox;
}

