#include "main.h"

#ifndef CANONBALL_H
#define CANONBALL_H


class CanonBall
{
public:
    CanonBall(){};
    CanonBall(float x, float y,float z);
    glm::vec3 position;
    float rotation;
    float inc;
    glm::vec3 direction;
    void draw(glm::mat4 VP);
    void tick();
    float initx;
    float initz;
    int tick_time;
    double speedx;
    double speedy;
    double speedz;
    int flag_air;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // CANONBALL_H
