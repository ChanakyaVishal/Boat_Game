#include "ganondorf.h"
#include "main.h"

Ganondorf::Ganondorf(float x, float y, float z)
{
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->starting_point_x = x;
    this->starting_point_z = z;
    this->health = 5;
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
    for (int i=0 ;i<12*3*3;i++) cube[i] *= 10;
    GLfloat cube_2[] = {
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
    for (int i=0 ;i<12*3*3;i++) cube_2[i] *= 5;
    for (int i=0 ;i<12*3*3;i++) if(i%3 == 1)cube_2[i] += 5;
 this->object = create3DObject(GL_TRIANGLES, 12*3, cube, COLOR_BLACK, GL_FILL);
     this->object2 = create3DObject(GL_TRIANGLES, 12*3, cube, COLOR_BLACK, GL_FILL);
}

void Ganondorf::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);
}

void Ganondorf::tick(){
   this->direction = glm::vec3(-sin(this->rotation * M_PI / 180.0f), 0, -cos(this->rotation * M_PI / 180.0f));
}

bounding_box_t Ganondorf::bounding_box_2() {
    float x = this->position.x, y = this->position.y, z = this->position.z;
    bounding_box_t bbox = { x,y, z, 15,15,15};
        return bbox;
    }

bounding_box_t Ganondorf::bounding_box() {
    float x = this->position.x, y = this->position.y, z = this->position.z;
    bounding_box_t bbox = { x,y, z, 70,70,70};
        return bbox;
    }



