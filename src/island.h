#include "main.h"

#ifndef ISLAND_H
#define ISLAND_H


class Island
{
public:
    Island(){};
    Island(float x, float y,float z);
    glm::vec3 position;
    float rotation;
    glm::vec3 direction;
    void draw(glm::mat4 VP);
    bounding_box_t bounding_box();
private:
    VAO *object;
     VAO *object1;
     VAO *object2;
     VAO *object3;
     VAO *object4;
};

#endif // ISLAND_H
