#include "main.h"

#ifndef TRIFORCE_H
#define TRIFORCE_H


class Triforce
{
public:
    Triforce(){};
    Triforce(float x, float y,float z);
    glm::vec3 position;
    float rotation;
    glm::vec3 direction;
    void draw(glm::mat4 VP);
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // TRIFORCE_H
