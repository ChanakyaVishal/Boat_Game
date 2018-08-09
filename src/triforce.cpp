#include "triforce.h"
#include "main.h"

Triforce::Triforce(float x,float y,float z){
    this->position = glm::vec3(x, y, z);
    this->rotation = 5;
    GLfloat cube[] = {
               0.5f, 0.0f, 0.0f,
               0.0f,1.0f, 0.0f,
                -0.5f, 0.0f, 0.0f,
                            0.5f, 0.0f, 0.4f,
                            0.0f,1.0f, 0.4f,
                             -0.5f, 0.0f, 0.4f,
            0.5f, 0.0f, 0.0f,
            0.0f,1.0f, 0.0f,
             0.5f, 0.0f, 0.4f,
                                0.5f, 0.0f, 0.4f,
                                0.0f,1.0f, 0.0f,
                                 0.0f, 1.0f, 0.4f,
            -0.5f, 0.0f, 0.0f,
            0.0f,1.0f, 0.0f,
            - 0.5f, 0.0f, 0.4f,
                                -0.5f, 0.0f, 0.4f,
                                0.0f,1.0f, 0.0f,
                                 0.0f, 1.0f, 0.4f,
            0.5f, 0.0f, 0.0f,
            0.5f,0.0f, 0.4f,
             -0.5f, 0.0f, 0.0f,
                                0.5f, 0.0f, 0.4f,
                                -0.5f,0.0f, 0.0f,
                                 -0.5f, 0.0f, 0.4f,
           };
         for (int i=0 ;i<8*3*3;i++) cube[i] *= 2;

 this->object = create3DObject(GL_TRIANGLES, 3*8, cube, COLOR_TRIFORCE, GL_FILL);
}


void Triforce::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

bounding_box_t Triforce::bounding_box() {
    float x = this->position.x, y = this->position.y, z = this->position.z;
    bounding_box_t bbox = { x,y, z, 1,1,1};
        return bbox;
    }
