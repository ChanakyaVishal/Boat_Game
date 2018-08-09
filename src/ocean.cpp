#include "ocean.h"
#include "main.h"

Ocean::Ocean(float x,float y)
{
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;


    GLfloat vertex_buffer_data[] = {
        -1000.0f,0.0f,-1000.0f, // triangle 1 : begin
        1000.0f,0.0f, -1000.0f,
        -1000.0f, 0.0f, 1000.0f, // triangle 1 : end
        1000.0f, 0.0f,-1000.0f, // triangle 2 : begin
        -1000.0f,0.0f,1000.0f,
        1000.0f, 0.0f,1000.0f, // triangle 2 : end

    };
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_BLUE, GL_FILL);
}

void Ocean::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

