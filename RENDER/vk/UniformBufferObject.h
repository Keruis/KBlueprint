#ifndef DEMO_UNIFORMBUFFEROBJECT_H
#define DEMO_UNIFORMBUFFEROBJECT_H

#include "../../Math/MMat.h"
#include <glm/glm.hpp>

struct UniformBufferObject {
//    Math::Mat::MatF44 model;
//    Math::Mat::MatF44 view;
//    Math::Mat::MatF44 proj;
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
};

#endif //DEMO_UNIFORMBUFFEROBJECT_H
