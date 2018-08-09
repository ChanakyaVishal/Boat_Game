#include "main.h"

#ifndef LINK_H
#define LINK_H


class Link
{
public:
    Link(){};
    Link(float x, float y,float z);
    glm::vec3 position;
    float rotation;
    float starting_point_x;
    float starting_point_z;
    int dir_flag;
    glm::vec3 direction;
    double speedx;
    double speedy;
    double speedz;
    int flag_air;
    void tick();
    void draw(glm::mat4 VP);
    bounding_box_t bounding_box();
    bounding_box_t bounding_box_2();
private:
    VAO *object;
};

#endif // LINK_H
