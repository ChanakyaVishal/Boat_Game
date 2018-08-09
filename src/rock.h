#include "main.h"

#ifndef Rock_H
#define Rock_H


class Rock
{
public:
    Rock(){};
    Rock(float x, float y,float z);
    glm::vec3 position;
    float rotation;
    glm::vec3 direction;
    void draw(glm::mat4 VP);
    bounding_box_t bounding_box();
private:
    VAO *object;
};


#endif // ROCK_H
