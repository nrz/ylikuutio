#ifndef CONTROLS_HPP
#define CONTROLS_HPP

extern glm::vec3 position;
extern float horizontalAngle;
extern float verticalAngle;
extern float initialFoV;

namespace controls
{
    void computeMatricesFromInputs();
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
}

#endif
