#include "main.h"

#ifndef BOOSTER_H
#define BOOSTER_H


class Booster
{
public:
    Booster(){};
    Booster(float x, float y,float z);
    glm::vec3 position;
    float rotation;
    glm::vec3 direction;
    void draw(glm::mat4 VP);
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BOOSTER_H
