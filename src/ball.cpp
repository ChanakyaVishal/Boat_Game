#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(0,0,0);
    this->rotation = 0;
    this->triforce_count = 0;
    this->speedx = 0;
    this->speedz = 0;
    this->rotation = 0;
    this->booster_time = 0;
    this->flag_air = 0;
    this->booster_count = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[10*108];
    insert_cube(vertex_buffer_data, 108*0, 0, 0, 0);
    for(int i=0; i<12*3*3; i++){
        if(i%3 == 0) vertex_buffer_data[i] *= 2.7;
        if(i%3 == 1) vertex_buffer_data[i] *= 0.8;
        if(i%3 == 2) vertex_buffer_data[i] *=2.7;
    }
    GLfloat triangle[] = {
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
         for (int i=0 ;i<8*3*3;i++) triangle[i] *= 6;
    this->object = create3DObject(GL_TRIANGLES, 12*3*3, vertex_buffer_data, COLOR_RED, GL_FILL);
  this->object2 = create3DObject(GL_TRIANGLES, 8*3, triangle, COLOR_GREEN, GL_FILL);
         this->object3 = create3DObject(GL_TRIANGLES, 12*3*3, vertex_buffer_data, COLOR_OCTOROK, GL_FILL);
         for(int i=0; i<12*3*3; i++){
             if(i%3 == 2) vertex_buffer_data[i] *= 2;
         }
            this->object4 = create3DObject(GL_TRIANGLES, 12*3*3, vertex_buffer_data, COLOR_RED, GL_FILL);


}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);

translate = glm::translate (glm::vec3(0,0,-2));
    rotate    = glm::rotate((float) (-90 * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
   MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object2);

    translate = glm::translate (glm::vec3(0,0,2));
        rotate    = glm::rotate((float) (-90 * M_PI / 180.0f), glm::vec3(1, 0, 0));
        Matrices.model *= (translate * rotate);
       MVP = VP * Matrices.model;
        glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
        draw3DObject(this->object3);

        translate = glm::translate (glm::vec3(0,0,-2));
            rotate    = glm::rotate((float) (-90 * M_PI / 180.0f), glm::vec3(0, 0, 1));
            Matrices.model *= (translate * rotate);
           MVP = VP * Matrices.model;
            glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
            draw3DObject(this->object4);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
    this->direction = glm::vec3(-sin(this->rotation * M_PI / 180.0f), 0, -cos(this->rotation * M_PI / 180.0f));
    int boost = 1;
    if(this->booster_time > 0) boost = this->booster_time/40.00;

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

void Ball::insert_cube(GLfloat *vertex_buffer_data, int index, float x, float y, float z){

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

    for(int i=0; i<108; i++){
        if(i%3 == 0) vertex_buffer_data[index + i] = x+cube[i];
        if(i%3 == 1) vertex_buffer_data[index + i] = y+cube[i];
        if(i%3 == 2) vertex_buffer_data[index + i] = z+cube[i];
    }
}

bounding_box_t Ball::bounding_box() {
    float x = this->position.x,y = this->position.y, z =this->position.z;
    bounding_box_t bbox = { x, y, z, 10,4,4 };
    return bbox;
}
