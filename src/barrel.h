#include "main.h"

#ifndef Barrel_H
#define Barrel_H


class Barrel
{
public:
    Barrel(){};
    Barrel(float x, float y,float z);
    glm::vec3 position;
    float rotation;
    glm::vec3 direction;
    void draw(glm::mat4 VP);
    bounding_box_t bounding_box();
private:
    VAO *object;
};


#endif // BARREL_H
