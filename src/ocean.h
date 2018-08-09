#include "main.h"

#ifndef OCEAN_H
#define OCEAN_H


class Ocean
{
public:
    Ocean(){};
    Ocean(float x, float y);
    glm::vec3 position;
    float rotation;
    glm::vec3 direction;
    void draw(glm::mat4 VP);
private:
    VAO *object;
};

#endif // OCEAN_H
