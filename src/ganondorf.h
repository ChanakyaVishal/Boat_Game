#include "main.h"
#ifndef GANONDORF_H
#define GANONDORF_H


class Ganondorf
{
public:
    Ganondorf(){};
    Ganondorf(float x, float y,float z);
    glm::vec3 position;
    float rotation;
    float starting_point_x;
    float starting_point_z;
    int health;
    int dir_flag;
    glm::vec3 direction;
    void draw(glm::mat4 VP);
    void tick();
    bounding_box_t bounding_box();
    bounding_box_t bounding_box_2();
private:
    VAO *object;
    VAO *object2;
};

#endif // GANONDORF_H
