#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    float triforce_count;
    glm::vec3 direction;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void insert_cube(GLfloat *vertex_buffer_data, int index, float x, float y, float z);
    void tick();
    int flag_air;
    int booster_count;
    int booster_time;
    double speedx;
    double speedy;
    double speedz;
    bounding_box_t bounding_box();
private:
    VAO *object;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
    VAO *object6;
    VAO *object7;
    VAO *object8;
};

#endif // BALL_H
