#include "main.h"

#ifndef OCTOROK_H
#define OCTOROK_H


class Octorok
{
public:
    Octorok(){};
    Octorok(float x, float y,float z);
    glm::vec3 position;
    float rotation;
    float starting_point_x;
    float starting_point_z;
    int dir_flag;
    glm::vec3 direction;
    void draw(glm::mat4 VP);
    bounding_box_t bounding_box();
    bounding_box_t bounding_box_2();
private:
    VAO *object;
};

#endif //
